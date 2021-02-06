#pragma once
#include "inc.h"

extern "C" u64 primeNumberCheck(u64 max);
extern "C" u64 primeNumberCheckOp(u64 max, u64 start);

double asmPrimeNumber(u64 max) {
	u64 primes = 0;
	u64 startTime = getCurrentTimeMS();
	primes = primeNumberCheckOp(max, 2);
	u64 endTime = getCurrentTimeMS();
	printf("ASM\n");
	printStuff(startTime, endTime, primes, max);
	double out = (double)endTime - (double)startTime;
	out /= 1000;
	return out;
}

void asmPrimeTestThreadFunction(u64 start, u64 end, double*completeTime, u64*primeReturn) {
	double timeTaken = 0;
	u64 primes=0;
	u64 startTime = getCurrentTimeMS();
	primes = primeNumberCheckOp(end, start);
	u64 endTime = getCurrentTimeMS();
	timeTaken = (double)endTime - (double)startTime;
	timeTaken /= 1000;
	*completeTime = timeTaken;
	*primeReturn = primes;
}

void asmPrimeTestThreads(u64 max, u64 amountOfTests, u64 maxThreads, double* averageTime) {
	double average = 0;
	u64 primeOut = 0;
	const u64 threads = 2;
	thread t[threads];
	double times[threads];
	u64 primes[threads];
	u64 threadStartIndex[threads];
	u64 threadEndIndex[threads];

	threadStartIndex[0] = 2;
	threadStartIndex[1] = max/2;

	threadEndIndex[0] = max/2;
	threadEndIndex[1] = max;

	for (u64 i = 0; i < threads; i++)
		t[i] = thread(asmPrimeTestThreadFunction, threadStartIndex[i], threadEndIndex[i], &times[i], &primes[i]);
	for (u64 i = 0; i < threads; i++) {
		t[i].join();
		average += times[i];
		primeOut += primes[i];
	}
	//primeOut /= threads;
	//average /= threads;
	average /= (double)amountOfTests;
	printf("ASM Prime Threads:\n");
	printf("Amount of primes: %llu\n", primeOut);
	printf("Average time: %llf\n\n", average);

	
	*averageTime = average;
}