#pragma once
#include <iostream>
#include <chrono>
#include <stdio.h>
#include <thread>
#include <immintrin.h>

typedef unsigned long long u64;
using namespace std;

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

#include "intrinFuncs.h"
#include "asmFuncs.h"
#include "cppFuncs.h"