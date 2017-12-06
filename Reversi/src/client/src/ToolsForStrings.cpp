/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex3
 **************************************/

#include "ToolsForStrings.h"
using namespace std;

/***************************************
 * Function Name: myToString
 * The Input: a number
 * The Output: the number as a string
 * The Function Operation: going through
 *  the digits and converting them to
 *  chars
 **************************************/
char *myToString(int number) {
	int length = 1;
	int indexer;
	int *numberInArr;
	char *charInArr;
	int tempNumber = number;

	while ((tempNumber /= 10) > 0) {
		length++;
	}

	numberInArr = new int[length];
	charInArr = new char[length + 1];
	tempNumber = number;

	for (indexer = length - 1; indexer >= 0; indexer--) {
		numberInArr[indexer] = tempNumber % 10;
		tempNumber /= 10;
	}

	for (indexer = 0; indexer < length; indexer++) {
		charInArr[indexer] = numberInArr[indexer] + '0';
	}
	charInArr[length] = '\0';

	delete [] numberInArr;
	return charInArr;
}

bool replaceStringWithString(string& replacee, const string& toReplace, const string& replaceWith) {
	size_t startPos = replacee.find(toReplace);
	if (startPos == string::npos) {
		return false;
	} else {
		replacee.replace(startPos, toReplace.length(), replaceWith);
		return true;
	}
}

std::pair<int, int> extractPairFromString(std::string& theString) {
	int x = 0;
	int y = 0;
	string xStr = "";
	string yStr = "";

	bool yNow = false;

	for (int index = 0; index < theString.size(); index++) {
		if ('0' <= theString[index] && theString[index] <= '9') {
			if (!yNow) {
				xStr += theString[index];
			} else {
				yStr += theString[index];
			}
		} else {
			yNow = true;
		}
	}
	stringstream xStream(xStr);
	stringstream yStream(yStr);

	xStream >> x;
	yStream >> y;

	return make_pair(x,y);
}
