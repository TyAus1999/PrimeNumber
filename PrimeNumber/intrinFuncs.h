#pragma once
#include "inc.h"

u64 intrinPrimeD(u64 max) {
	max = max - (max % 4);
	u64 amountOfPrimes = 2;
	__m256d one = _mm256_set1_pd(1.0);
	__m256d zero = _mm256_setzero_pd();
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
			bottom = _mm256_add_pd(bottom, one);
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

u64 intrinPrimeDOptimized(u64 max) {
	max = max - (max % 4);
	u64 amountOfPrimes = 2;
	__m256d one = _mm256_set1_pd(1.0);
	__m256d zero = _mm256_setzero_pd();
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
			//Compare if the amount of all the factors is greater than 1
			//If so then all numbers are garbage
			__m256d checkFactors = _mm256_cmp_pd(factors, one, 13);
			__m256i test = _mm256_castpd_si256(factors);
			double value = _mm256_cvtsd_f64(_mm256_castsi256_pd(test));
			test = _mm256_slli_epi64(test, 64);
			double value2 = _mm256_cvtsd_f64(_mm256_castsi256_pd(test));
			test = _mm256_slli_epi64(test, 64);
			bottom = _mm256_add_pd(bottom, one);
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