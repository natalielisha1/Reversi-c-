/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex4
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
	int negative = 0;

	if (number < 0) {
		negative = 1;
		number *= (-1);
		tempNumber *= (-1);
	}

	while ((tempNumber /= 10) > 0) {
		length++;
	}

	numberInArr = new int[length];
	charInArr = new char[length + 1 + negative];
	tempNumber = number;

	for (indexer = length - 1; indexer >= 0; indexer--) {
		numberInArr[indexer] = tempNumber % 10;
		tempNumber /= 10;
	}

	for (indexer = 0; indexer < length; indexer++) {
		charInArr[indexer + negative] = numberInArr[indexer] + '0';
	}
	charInArr[length + negative] = '\0';
	if (negative == 1) {
		charInArr[0] = '-';
	}

	delete [] numberInArr;
	return charInArr;
}

/***************************************
 * Function Name: replaceStringWithString
 * The Input: string to replace inside it
 *            string to find
 *            string to replace with
 * The Output: true - successful replacement
 *             false - otherwise
 * The Function Operation: finding the
 *  location of "toReplace" and replacing
 *  it
 **************************************/
bool replaceStringWithString(string& replacee, const string& toReplace, const string& replaceWith) {
	size_t startPos = replacee.find(toReplace);
	if (startPos == string::npos) {
		return false;
	} else {
		replacee.replace(startPos, toReplace.length(), replaceWith);
		return true;
	}
}

/***************************************
 * Function Name: extractPairFromString
 * The Input: string to extract from
 * The Output: the pair
 * The Function Operation: going through
 *  the chars and dividing them to x and
 *  y coords, and returning them as a
 *  pair of ints
 **************************************/
std::pair<int, int> extractPairFromString(std::string& theString) {
	int x = 0;
	int y = 0;
	string xStr = "";
	string yStr = "";

	bool yNow = false;

	//Going through the chars until the space chars, and after
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
	//Converting strings to ints
	stringstream xStream(xStr);
	stringstream yStream(yStr);

	xStream >> x;
	yStream >> y;

	return make_pair(x,y);
}

vector<string> splitString(string& toSplit, char splitter) {
	vector<string> toReturn;
	char temp[2] = {0};

	string curr = "";
	for (int i = 0; i < toSplit.length(); i++) {
		if (toSplit[i] == splitter) {
			toReturn.push_back(curr);
			curr = "";
			continue;
		}
		temp[0] = toSplit[i];
		curr.append(temp);
	}
	toReturn.push_back(curr);

	return toReturn;
}
