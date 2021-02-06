#include "inc.h"

using namespace std;
int main() {
	u64 tests = 1;
	u64 max = 100000;
	double averageCPP=0;
	double averageASM=0;

	thread cppThread(cppPrimeTestThreads, max, tests, 1, &averageCPP);
	thread asmThread(asmPrimeTestThreads, max, tests, 1, &averageASM);
	//u64 primes=intrinPrimeD(max);
	//printf("Amount of primes: %llu\n", primes);
	double completeTime=0;
	u64 primeReturn=0;
	asmPrimeTestThreadFunction(2, max, &completeTime, &primeReturn);
	printf("OP Test Non Thread\n");
	printf("Took: %llfs\n",completeTime);
	printf("Amount of primes: %llu\n", primeReturn);
	printf("=============================\n");
	
	//cppPrimeTestThreads(max, tests, 1, &averageCPP);
	//asmPrimeTestThreads(max, tests, 1, &averageASM);
	asmThread.join();
	cppThread.join();
	
	printf("Amount of times tested: %llu\n", tests);
	printf("Max number: %llu\n", max);
	if (averageCPP > 60.0) {
		double minutes=averageCPP/60.0;
		double decimals = minutes - floor(minutes);
		minutes = floor(minutes);
		decimals *= 60;
		printf("Average time for C++: %llfm:%llfs", minutes, decimals);
	}
	else
		printf("Average time for C++: %llfs\n", averageCPP);
	if (averageASM > 60.0) {
		double minutes = averageASM / 60.0;
		double decimals = minutes - floor(minutes);
		minutes = floor(minutes);
		decimals *= 60;
		printf("Average time for ASM: %llfm:%llfs", minutes, decimals);
	}
	else
		printf("Average time for ASM: %llfs\n", averageASM);
	return 0;
}