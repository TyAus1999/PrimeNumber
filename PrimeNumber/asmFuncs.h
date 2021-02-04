#pragma once
#include "inc.h"

extern "C" u64 primeNumberCheck(u64 max);
extern "C" u64 primeNumberCheckOp(u64 max);

double asmPrimeNumber(u64 max) {
	u64 primes = 0;
	u64 startTime = getCurrentTimeMS();
	primes = primeNumberCheckOp(max);
	u64 endTime = getCurrentTimeMS();
	printf("ASM\n");
	printStuff(startTime, endTime, primes, max);
	double out = (double)endTime - (double)startTime;
	out /= 1000;
	return out;
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