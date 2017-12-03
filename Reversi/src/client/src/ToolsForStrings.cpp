/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex3
 **************************************/

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