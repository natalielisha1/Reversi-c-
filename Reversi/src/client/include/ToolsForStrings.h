/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex3
 **************************************/

#ifndef TOOLSFORSTRINGS_H_
#define TOOLSFORSTRINGS_H_

#include <string>
#include <utility>
#include <sstream>

char *myToString(int number);

bool replaceStringWithString(std::string& replacee,
							 const std::string& toReplace,
							 const std::string& replaceWith);

std::pair<int, int> extractPairFromString(std::string& theString);

#endif /* TOOLSFORSTRINGS_H_ */
