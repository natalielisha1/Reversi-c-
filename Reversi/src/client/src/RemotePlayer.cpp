/*
 * RemotePlayer.cpp
 *
 *  Created on: Dec 3, 2017
 *      Author: ofek286
 */

#include "RemotePlayer.h"
using namespace std;

RemotePlayer::RemotePlayer(Board::Cell type): Player(type), client() {
	client.connectToServer();
	cout << "Waiting for other player to join..." << endl;
	int order = client.getOrder();
	if (order == 1) {
		this->type = Board::O;
	} else if (order == 2) {
		this->type = Board::X;
	}
}

RemotePlayer::~RemotePlayer() {
	client.disconnect();
}

Point RemotePlayer::makeMove(vector<Point>* options, Point bestMove) {
	cout << "Waiting for other player's move..." << endl;

	string noMove = "NoMove";

	string moveMsg = client.readMessage();
	if (strcmp(moveMsg.c_str(), noMove.c_str()) == 0) {
		return Point(-1,-1);
	}

	Point theMove = Point(extractPairFromString(moveMsg));
	--theMove;

	return theMove;
}

void RemotePlayer::sendMessage(const char* message) {
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

	static bool boardPrinting = false;
	static int noMoveCounter = 0;

	string msgStr(message);

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
		//client.sendMessage(xMove.c_str());
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
		//client.sendMessage(oMove.c_str());
		return;
	}

	if (boardPrinting) {
		string temp = string(message);
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
			cout << message << endl;
			return;
		}
	}
}
