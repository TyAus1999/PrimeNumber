#include "inc.h"

using namespace std;
int main() {
	u64 tests = 5;
	u64 max = 1000000;
	double averageCPP=0;
	double averageASM=0;

	thread cppThread(cppPrimeTestThreads, max, tests, 1, &averageCPP);
	thread asmThread(asmPrimeTestThreads, max, tests, 1, &averageASM);
	//u64 primes=intrinPrimeD(max);
	//printf("Amount of primes: %llu\n", primes);
	
	
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