/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex7
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

/***************************************
 * Function Name: extractCommand
 * The Input: a reference to a message
 * The Output: a pair of a command and
 * a suitable vector of arguments
 * The Function Operation: extracting a command
 * based on the given message
 **************************************/
pair<string, vector<string> > extractCommand(string& msg) {
	string command;
	vector<string> args;
	string currentWord = "";
	bool foundCommand = false;

	if (msg.find(" ") == string::npos) {
		return make_pair(msg, args);
	}

	size_t index = 0;
	while ((index = msg.find(" ")) != string::npos) {
		currentWord = msg.substr(0, index);
		if (!foundCommand) {
			command = currentWord;
			foundCommand = true;
		} else {
			args.push_back(currentWord);
		}
		msg = msg.substr(index + 1);
	}
	args.push_back(msg);

	return make_pair(command, args);
}
