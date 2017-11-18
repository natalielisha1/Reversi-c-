/*
 * test_factorial.cpp
 *
 *  Created on: Nov 17, 2017
 *      Author: ofek286
 */
#include "gtest/gtest.h"
#include "factorial.h"

#include <stdexcept>

//Tests factorial of positive numbers
TEST(FactorialTest, HandlesPositiveInput) {
	EXPECT_EQ(factorial(1), 1);
	EXPECT_EQ(factorial(2), 2);
	EXPECT_EQ(factorial(5), 120);
	EXPECT_EQ(factorial(8), 40320);
}

//Tests factorial of 0
TEST(FactorialTest, HandlesZeroInput) {
	EXPECT_EQ(factorial(0), 1);
}

//Tests factorial of negative numbers
TEST(FactorialTest, HandlesNegativeInput) {
	EXPECT_EQ(factorial(-1), 1);
	EXPECT_EQ(factorial(-5), 1);
}

TEST(FactorialTest, CheckOverflow) {
	EXPECT_THROW(factorial(13), std::overflow_error);
}
