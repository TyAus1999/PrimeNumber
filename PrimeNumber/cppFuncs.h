#pragma once
#include "inc.h"

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

void cppPrimeTestThreads(u64 max, u64 amountOfTests, u64 maxThreads, double* averageTime) {
	double average = 0;
	for (u64 i = 0; i < amountOfTests; i++) {
		printf("C++ Iteration %llu\n", i);
		average += cppPrime(max);
		printf("\n");
	}
	average /= (double)amountOfTests;
	*averageTime = average;
}