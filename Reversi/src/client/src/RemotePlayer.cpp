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
	cout << "Connecting to the server" << endl;
	//Connecting to the server
	client.connectToServer();

	int option = 0;
	string msgToSend;
	string gameID;
	string result;
	do {
		cout << "Choose your option:" << endl;
		cout << "1. Start a new game" << endl;
		cout << "2. Join an existing game" << endl;
		cin >> option;

		switch (option) {
			case 1: {
				result = "";
				gameID = "";
				while (result != "OK") {
					gameID = client.genUniqueGameIdentifier();
					msgToSend = "start ";
					msgToSend.append(gameID);
					client.sendMessage(msgToSend.c_str());
					result = client.readShortMessage();
					if (result == "NULL") {
						cout << "The server disconnected. goodbye." << endl;
						//type = empty, so the game will shutdown gracefully
						this->type = Board::Empty;
						return;
					}
				}
				cout << "Your game ID is " << gameID << endl;
				cout << "Waiting for a player to join the game..." << endl;
				break;
			}
			case 2: {
				msgToSend = "list_games";
				client.sendMessage(msgToSend.c_str());
				result = client.readMessage();
				if (result == "NONE") {
					cout << "There are no available games to join." << endl;
					option = 0;
				} else if (result == "NULL") {
					cout << "The server disconnected. goodbye." << endl;
					//type = empty, so the game will shutdown gracefully
					this->type = Board::Empty;
					return;
				} else {
					vector<string> availableGames = splitString(result, ',');
					cout << "Available games: (enter the game index)" << endl;
					int gameIndex = 0;
					for (vector<string>::iterator it = availableGames.begin(); it != availableGames.end(); ++it) {
						cout << gameIndex << ". " << *it << endl;
						gameIndex++;
					}
					int chosenGame = 0;
					cin >> chosenGame;

					gameID = availableGames.at(chosenGame);
					msgToSend = "join ";
					msgToSend.append(gameID);
					client.sendMessage(msgToSend.c_str());
					result = client.readShortMessage();
					if (result == "OK") {
						client.setGameName(gameID);
					} else {
						cout << "Joining the game failed." << endl;
						option = 0;
					}
				}
			}
		}

	} while (option != 1 && option != 2);
	//Getting the order
	int order = client.getOrder();
	if (order == 1) {
		this->type = Board::O;
	} else if (order == 2) {
		this->type = Board::X;
	} else if (order == -1) {
		cout << "The server disconnected. goodbye." << endl;
		//type = empty, so the game will shutdown gracefully
		this->type = Board::Empty;
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

	//Creating strings to compare to
	string noMove = "NoMove";
	string end = "END";

	//Getting the message
	string moveMsg = client.readMessage();

	//Doing the comparisons
	if (moveMsg == noMove) {
		return Point(-1,-1);
	}
	if (moveMsg == end) {
		return Point(-2,-2);
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
	string space = " ";

	string xWon = "X player won!";
	string oWon = "O player won!";
	string tie = "It's a tie!";

	string xMove = "X: It's your move";
	string oMove = "O: It's your move";

	string boardPrintTitle = "Current board:";

	string xPlayed = "X played ";
	string oPlayed = "O played ";

	string gameEnded = "Game Ended!";

	//Creating vars to know if the message shouldn't be sent
	static bool boardPrinting = false;
	static int noMoveCounter = 0;

	string msgStr(message);

	//Checking the message, and reacting accordingly
	if (msgStr == xWon) {
		string temp = "close ";
		temp.append(client.getGameName());
		client.sendMessage(temp.c_str());
		return;
	}
	if (msgStr == oWon) {
		string temp = "close ";
		temp.append(client.getGameName());
		client.sendMessage(temp.c_str());
		return;
	}
	if (msgStr == tie) {
		string temp = "close ";
		temp.append(client.getGameName());
		client.sendMessage(temp.c_str());
		return;
	}
	if (msgStr == gameEnded) {
		//Do nothing - it shouldn't have happened
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
					client.sendMessage("play NoMove");
				}
				noMoveCounter++;
			} else {
				client.sendMessage("play NoMove");
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
					client.sendMessage("play NoMove");
				}
				noMoveCounter++;
			} else {
				client.sendMessage("play NoMove");
				noMoveCounter++;
			}
		}
		boardPrinting = false;
		return;
	}

	//The board should be printed locally
	if (boardPrinting) {
		string temp = "play ";
		temp.append(msgStr);
		//The move should be sent
		if (temp.find(xPlayed) != string::npos) {
			boardPrinting = false;
			replaceStringWithString(temp, xPlayed, blank);
			replaceStringWithString(temp, openBrackets, blank);
			replaceStringWithString(temp, closingBrackets, blank);
			replaceStringWithString(temp, commaNoSpace, space);
			client.sendMessage(temp.c_str());
			return;
		} else if (temp.find(oPlayed) != string::npos) {
			boardPrinting = false;
			replaceStringWithString(temp, oPlayed, blank);
			replaceStringWithString(temp, openBrackets, blank);
			replaceStringWithString(temp, closingBrackets, blank);
			replaceStringWithString(temp, commaNoSpace, space);
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
