#include <iostream>
#include <chrono>
#include <stdio.h>
#include <thread>
#include <immintrin.h>

using namespace std;

typedef long long u64;

//start is where it starts
//max is when it stops, lessthan or equal
//returns amount of primes
extern "C" u64 primeNumberCheck(u64 max);

u64 getCurrentTimeMS() {
	u64 out = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	return out;
}

void printStuff(u64 startTime, u64 endTime, u64 amountOfPrimes, u64 maxNumber) {
	printf("Amount of Prime Numbers: %llu\n", amountOfPrimes);
	double seconds = (double)endTime - (double)startTime;
	seconds /= 1000;
	printf("Amount of time taken: %llfs\n", seconds);
	printf("Max number tested to: %llu\n", maxNumber);
}

double asmPrimeNumber(u64 max) {
	u64 primes = 0;
	u64 startTime = getCurrentTimeMS();
	primes=primeNumberCheck(max);
	u64 endTime = getCurrentTimeMS();
	printf("ASM\n");
	printStuff(startTime, endTime, primes, max);
	double out = (double)endTime - (double)startTime;
	out /= 1000;
	return out;
}

double cppPrime(u64 maxNumber) {
	u64 amountOfPrimes = 0;
	u64 startTime = getCurrentTimeMS();
	for (u64 test = 2; test <= maxNumber; test++) {
		u64 factors = 0;
		for (u64 toTest = 2; toTest < test; toTest++) {
			if (test % toTest == 0) {
				factors++;
				if (factors > 1)
					break;
			}
		}
		if (factors == 0)
			amountOfPrimes++;
	}
	u64 endTime = getCurrentTimeMS();
	printf("C++\n");
	printStuff(startTime, endTime, amountOfPrimes, maxNumber);
	double out = (double)endTime - (double)startTime;
	out /= 1000;
	return out;
}

void cppPrimeTestThreads(u64 max, u64 amountOfTests, u64 maxThreads, double *averageTime) {
	double average = 0;
	for (u64 i = 0; i < amountOfTests; i++) {
		printf("C++ Iteration %llu\n",i);
		average += cppPrime(max);
		printf("\n");
	}
	average /= (double)amountOfTests;
	*averageTime = average;
}

void asmPrimeTestThreads(u64 max, u64 amountOfTests, u64 maxThreads, double* averageTime) {
	double average = 0;
	for (u64 i = 0; i < amountOfTests; i++) {
		printf("ASM Iteration %llu\n", i);
		average += asmPrimeNumber(max);
		printf("\n");
	}
	average /= (double)amountOfTests;
	*averageTime = average;
}

//Max should be a multiple of 4
u64 intrinPrimeD(u64 max) {
	/*
	u64 testIntegers[4];
	for (u64 i = 0; i < 4; i++)
		testIntegers[i] = 2 + i;
	__m128i vindex = _mm_set_epi32(0, 1, 2, 3);
	__m256i primeToTest = _mm256_i32gather_epi64(testIntegers, vindex, 8);
	__m256i startingNumbers = _mm256_set1_epi64x((u64)2);
	__m256i factors = _mm256_setzero_si256();
	__m256i one = _mm256_set1_epi64x((u64)1);

	primeToTest = _mm256_srli_epi64(primeToTest, 1);
	__m256i isEqual = _mm256_cmpeq_epi64(primeToTest, one);
	
	*/
	/*
	get remainder
	double top = 346;
	double bottom = 7;
	double nonFloored = top / bottom;
	double floored = floor(nonFloored);
	double mulValue = bottom * floored;
	double remainder = top - mulValue;
	*/
	/*u64 amountOfPrimes = 1;
	double testNumbers[4];
	for (int i = 0; i < 4; i++)
		testNumbers[i] = (double)(88 + i);
	__m256d one = _mm256_set1_pd(1.0);
	__m256d four = _mm256_set1_pd(4.0);
	__m256d initValues = _mm256_set1_pd(2.0);
	__m256d top = _mm256_load_pd(testNumbers);
	__m256d bottom = _mm256_movedup_pd(initValues);
	__m256d nonFloored = _mm256_div_pd(top, bottom);
	__m256d floored = _mm256_floor_pd(nonFloored);
	__m256d mulValue = _mm256_mul_pd(bottom, floored);
	__m256d remainders = _mm256_sub_pd(top, mulValue);
	__m256d eqoq = _mm256_cmp_pd(remainders, one, 0);
	double newNumbers[4];
	_mm256_maskstore_pd(newNumbers, _mm256_castpd_si256(eqoq), top);*/
	max = max - (max % 4);
	u64 amountOfPrimes = 2;
	__m256d one = _mm256_set1_pd(1.0);
	__m256d zero = _mm256_setzero_pd();
	__m256i neg1 = _mm256_set1_epi64x((long long)-1);
	__m256d initValuesTesting = _mm256_set1_pd(2.0);
	__m256d top, bottom, nonFloored, floored, mulValue, remainders, factors;
	double* nums = (double*)malloc(sizeof(double) * 8);
	for (u64 i = 4; i < max; i += 4) {
		top = _mm256_set_pd((double)i, (double)i + 1, (double)i + 2, (double)i + 3);
		bottom = _mm256_movedup_pd(initValuesTesting);
		factors = _mm256_movedup_pd(zero);
		for (u64 inner = 2; inner < i + 3; inner++) {
			nonFloored = _mm256_div_pd(top, bottom);
			floored = _mm256_floor_pd(nonFloored);
			mulValue = _mm256_mul_pd(bottom, floored);
			remainders = _mm256_sub_pd(top, mulValue);
			__m256d checkRemainders = _mm256_cmp_pd(remainders, zero, 0);
			__m256d greaterE1 = _mm256_cmp_pd(bottom, top, 1);
			__m256d checkMask = _mm256_and_pd(checkRemainders, greaterE1);
			__m256d addMask = _mm256_blendv_pd(zero, one, checkMask);
			factors = _mm256_add_pd(factors, addMask);
			bottom = _mm256_add_pd(bottom,one);
		}
		_mm256_store_pd(nums, factors);
		_mm256_store_pd(&nums[4], top);
		for (char after = 0; after < 4; after++) {
			if (nums[after] == 0)
				amountOfPrimes++;
		}
	}
	free(nums);

	return amountOfPrimes;
}


int main() {
	u64 tests = 1;
	u64 max = 500000;
	double averageCPP=0;
	double averageASM=0;

	thread cppThread(cppPrimeTestThreads, max, tests, 1, &averageCPP);
	thread asmThread(asmPrimeTestThreads, max, tests, 1, &averageASM);
	u64 primes=intrinPrimeD(max);
	printf("Amount of primes: %llu\n", primes);
	
	
	//cppPrimeTestThreads(max, tests, 1, &averageCPP);
	//asmPrimeTestThreads(max, tests, 1, &averageASM);
	asmThread.join();
	cppThread.join();
	
	printf("Amount of times tested: %llu\n", tests);
	printf("Max number: %llu\n", max);
	printf("Average time for C++: %llfs\n", averageCPP);
	printf("Average time for ASM: %llfs\n", averageASM);
	return 0;
}