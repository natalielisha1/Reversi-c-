/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex4
 **************************************/

#include "RemotePlayer.h"
using namespace std;

/***************************************
 * Function Name: RemotePlayer (Constructor)
 * The Input: the player's type
 * The Output: the new player
 * The Function Operation: init'ing the
 *  client, and getting the player's order
 **************************************/
RemotePlayer::RemotePlayer(Board::Cell type): Player(type), client() {
	//Connecting to the server
	client.connectToServer();
	//Waiting for the other player
	cout << "Waiting for other player to join..." << endl;
	//Getting the order
	int order = client.getOrder();
	if (order == 1) {
		this->type = Board::O;
	} else if (order == 2) {
		this->type = Board::X;
	}
}

/***************************************
 * Function Name: ~RemotePlayer (Destructor)
 * The Input: no input
 * The Output: no output
 * The Function Operation: closing the
 *  client
 **************************************/
RemotePlayer::~RemotePlayer() {
	client.disconnect();
}

/***************************************
 * Function Name: makeMove
 * The Input: options to put Cell, and the
 *  best move
 * The Output: the best move
 * The Function Operation: returning the
 *  best move
 **************************************/
Point RemotePlayer::makeMove(vector<Point>* options, Point bestMove) {
	//Waiting for the move
	cout << "Waiting for other player's move..." << endl;

	//Creating a string to compare to
	string noMove = "NoMove";
	//Getting the message
	string moveMsg = client.readMessage();
	if (moveMsg == noMove) {
		return Point(-1,-1);
	}
	//Returning the move from the message
	Point theMove = Point(extractPairFromString(moveMsg));
	//Aligning the point to the game
	--theMove;

	return theMove;
}

/***************************************
 * Function Name: sendMessage
 * The Input: the message
 * The Output: nothing
 * The Function Operation: checking what
 *  is the message and sending it when
 *  required
 **************************************/
void RemotePlayer::sendMessage(const char* message) {
	//Creating strings to compare to and to replace
	string blank = "";
	string openBrackets = "(";
	string closingBrackets = ")";
	string commaNoSpace = ",";
	string commaWithSpace = ", ";

	string xWon = "X player won!";
	string oWon = "O player won!";
	string tie = "It's a tie!";

	string xMove = "X: It's your move";
	string oMove = "O: It's your move";

	string boardPrintTitle = "Current board:";

	string xPlayed = "X played ";
	string oPlayed = "O played ";

	//Creating vars to know if the message shouldn't be sent
	static bool boardPrinting = false;
	static int noMoveCounter = 0;

	string msgStr(message);

	//Checking the message, and reacting accordingly
	if (msgStr == xWon) {
		client.sendMessage("END");
		return;
	}
	if (msgStr == oWon) {
		client.sendMessage("END");
		return;
	}
	if (msgStr == tie) {
		client.sendMessage("END");
		return;
	}

	if (msgStr == boardPrintTitle) {
		boardPrinting = true;
	}

	//No move was made, so send "NoMove"
	if (msgStr.find(xMove) != string::npos) {
		if (boardPrinting) {
			if (noMoveCounter == 0) {
				if (this->type == Board::O) {
					client.sendMessage("NoMove");
				}
				noMoveCounter++;
			} else {
				client.sendMessage("NoMove");
				noMoveCounter++;
			}
		}
		boardPrinting = false;
		return;
	}
	if (msgStr.find(oMove) != string::npos) {
		if (boardPrinting) {
			if (noMoveCounter == 0) {
				if (this->type == Board::O) {
					client.sendMessage("NoMove");
				}
				noMoveCounter++;
			} else {
				client.sendMessage("NoMove");
				noMoveCounter++;
			}
		}
		boardPrinting = false;
		return;
	}

	//The board should be printed locally
	if (boardPrinting) {
		string temp = string(message);
		//The move should be sent
		if (temp.find(xPlayed) != string::npos) {
			boardPrinting = false;
			replaceStringWithString(temp, xPlayed, blank);
			replaceStringWithString(temp, openBrackets, blank);
			replaceStringWithString(temp, closingBrackets, blank);
			replaceStringWithString(temp, commaNoSpace, commaWithSpace);
			client.sendMessage(temp.c_str());
			return;
		} else if (temp.find(oPlayed) != string::npos) {
			boardPrinting = false;
			replaceStringWithString(temp, oPlayed, blank);
			replaceStringWithString(temp, openBrackets, blank);
			replaceStringWithString(temp, closingBrackets, blank);
			replaceStringWithString(temp, commaNoSpace, commaWithSpace);
			client.sendMessage(temp.c_str());
			return;
		} else {
			//Printing the board locally
			cout << message << endl;
			return;
		}
	}
}

/***************************************
 * Function Name: getClient
 * The Input: the message
 * The Output: nothing
 * The Function Operation: returning the
 *  client
 **************************************/
Client RemotePlayer::getClient() const {
	return this->client;
}
