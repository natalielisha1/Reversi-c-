/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex7
 **************************************/

#include "HumanPlayer.h"
using namespace std;

/***************************************
 * Function Name: HumanPlayer (Constructor)
 * The Input: the player's type
 * The Output: the new player
 * The Function Operation: nothing
 **************************************/
HumanPlayer::HumanPlayer(Board::Cell type): Player(type) {}

/***************************************
 * Function Name: ~HumanPlayer (Destructor)
 * The Input: no input
 * The Output: no output
 * The Function Operation: nothing
 **************************************/
HumanPlayer::~HumanPlayer() {
	// Nothing right now
}

/***************************************
 * Function Name: makeMove
 * The Input: options to put Cell, and
 *  the best move
 * The Output: the chosen option
 * The Function Operation: asking the
 *  user to select the move, and
 *  returning the chosen option
 **************************************/
Point HumanPlayer::makeMove(vector<Point> *options, Point bestMove) {
	//Using dummies to fix cout/cin issues
	char dummy;

	//Clearing previous cin issues
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	if (options->size() == 0) {
		//There are no options to choose from
		cout << "No possible moves. Play passes back to ";
		cout << "the other player. Press any key to continue.";
		cout << endl;
		getchar();
		return Point(-1,-1);
	} else {
		//There are options to choose from
		bool foundPoint = false;
		while (!foundPoint) {
			//Printing the options
			cout << "Your possible moves: ";
			int indexer = 0;
			for (vector<Point>::iterator it = options->begin(); it != options->end(); ++it) {
				if (indexer != 0) {
					cout << ",";
				}
				(*it).printPoint();
				indexer++;
			}
			cout << endl << endl;
			//Asking for the option to use
			cout << "Please enter your move row,col:";
			int tempX, tempY;
			cin >> tempX;
			if (cin.fail()) {
				//The input was incorrect...
				cout << "Input against the format, try again" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
			cin >> dummy;
			cin >> tempY;
			if (cin.fail()) {
				cout << "Input against the format, try again" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
			cout << endl;
			//The input was correct, so use it
			Point tempPoint = Point(tempX, tempY);
			for (vector<Point>::iterator it = options->begin(); it != options->end(); ++it) {
				Point itPoint = *it;
				if (itPoint == tempPoint) {
					foundPoint = true;
					break;
				}
			}
			if (!foundPoint) {
				/*
				 * The input was correct format-wise, but the point
				 * is not available
				 */
				cout << "Option not available, choose again." << endl;
			} else {
				/*
				 * Returning the Point formatted in
				 * a way the board can understand
				 */
				--tempPoint;//.alignToPrint();
				return tempPoint;
			}
		}
	}
	return Point(-1, -1);
}

/***************************************
 * Function Name: sendMessage
 * The Input: the message
 * The Output: nothing
 * The Function Operation: printing
 *  the message
 **************************************/
void HumanPlayer::sendMessage(const char *message) {
	cout << message << endl;
}
