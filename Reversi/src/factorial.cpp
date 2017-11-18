/*
 * factorial.cpp
 *
 *  Created on: Nov 17, 2017
 *      Author: ofek286
 */
#include <limits.h>
#include <stdexcept>

int factorial(int n) {
	int result = 1;
	for (int i = 2; i <= n; i++) {
		if (result > INT_MAX /i)
			throw std::overflow_error("Overflow");
		result *= i;
	}
	return result;
}
