/*
 * gtest_main.cpp
 *
 *  Created on: Nov 17, 2017
 *      Author: ofek286
 */
#include "gtest/gtest.h"

GTEST_API_ int main1(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
