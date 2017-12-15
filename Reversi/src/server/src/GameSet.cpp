/*
 * GameSet.cpp
 *
 *  Created on: Dec 15, 2017
 *      Author: ofek286
 */

#include "GameSet.h"

using namespace std;

GameSet::GameSet(): lastCommand(GameSet::Debug), lastCommandResult(-1) {
	//Regular messages init
	firstPlayerMessage = string("1");
	secondPlayerMessage = string("2");

	//Error messages init
	noErrorMessage = string("1");
	gameExistsErrorMessage = string("-1");
	noArgsErrorMessage = string("-2");
	gameFullErrorMessage = string("-7");
}

GameSet::~GameSet() {
	//Nothing right now
}

void GameSet::debugMessage(int clientSocket, vector<string> args) {

}

void GameSet::startNewMatch(int clientASocket, vector<string> args) {
}

void GameSet::joinMatch(int clientBSocket, vector<string> args) {
	lastCommand = GameSet::Join;

	if (args.size() < 1) {
		lastCommandResult = ERROR_NO_ARGS_RESULT;
		return;
	}
	for (int i = 0; i < MAX_GAMES; i++) {
		if (matches[i].getGameName() == args[0]) {
			if (matches[i].getStatus() != GameInfo::XWaiting) {
				lastCommandResult = ERROR_GAME_FULL_RESULT;
				sendMessageToClient(clientBSocket, gameFullErrorMessage);
				return;
			} else {
				lastCommandResult = NO_ERROR_RESULT;
				int clientASocket = matches[i].getClientA();
				sendMessageToClient(clientASocket, firstPlayerMessage);
				sendMessageToClient(clientBSocket, secondPlayerMessage);
				return;
			}
		}
	}
	lastCommandResult = ERROR_GAME_DOES_NOT_EXIST_RESULT;
}

void GameSet::playMatch(int senderClient, string xLoc, string yLoc) {
	lastCommand = GameSet::Play;

	string toSend = string(xLoc);
	toSend.append(", ");
	toSend.append(yLoc);

	int currGameIndex = clientExists(senderClient);
	if (currGameIndex == -1) {
		lastCommandResult = ERROR_INVALID_CLIENT_RESULT;
		return;
	}
	GameInfo currGame = matches[currGameIndex];
	if (currGame.getStatus() != GameInfo::Playing) {
		lastCommandResult = ERROR_GAME_NOT_PLAYING_RESULT;
		return;
	}
	int otherClient = currGame.getOtherClient(senderClient);
	sendMessageToClient(otherClient, toSend);
	lastCommandResult = NO_ERROR_RESULT;
}

void GameSet::playMatch(int senderClient, string noMove) {
	lastCommand = GameSet::Play;

	string toCompare = "NoMove";
	int currGameIndex = clientExists(senderClient);
	if (currGameIndex == -1) {
		lastCommandResult = ERROR_INVALID_CLIENT_RESULT;
		return;
	}
	GameInfo currGame = matches[currGameIndex];
	if (currGame.getStatus() != GameInfo::Playing) {
		lastCommandResult = ERROR_GAME_NOT_PLAYING_RESULT;
		return;
	}
	if (noMove == toCompare) {
		int otherClient = currGame.getOtherClient(senderClient);
		sendMessageToClient(otherClient, noMove);
		lastCommandResult = NO_ERROR_RESULT;
	} else {
		lastCommandResult = ERROR_FAKE_NO_MOVE_RESULT;
	}
}

void GameSet::closeMatch(int senderClient, vector<string> args) {
	lastCommand = GameSet::Close;

	if (args.size() < 1) {
		lastCommandResult = ERROR_NO_ARGS_RESULT;
		return;
	}
	for (int i = 0; i < MAX_GAMES; i++) {
		if (matches[i].getGameName() == args[0]) {
			matches[i].setInterrupt(true);
			lastCommandResult = NO_ERROR_RESULT;
			return;
		}
	}
	lastCommandResult = ERROR_GAME_DOES_NOT_EXIST_RESULT;
}

void GameSet::listMatches(int senderClient) {
	lastCommand = GameSet::List;
	string toSend = "";
	for (int i = 0; i < MAX_GAMES; i++) {
		if (matches[i].getStatus() == GameInfo::XWaiting) {
			if (toSend != "") {
				toSend.append(",");
			}
			toSend.append(matches[i].getGameName());
		}
	}
	sendMessageToClient(senderClient, toSend);
	lastCommandResult = NO_ERROR_RESULT;
}

void GameSet::interruptMatches() {
	for (int i = 0; i < MAX_GAMES; i++) {
		matches[i].setInterrupt(true);
	}
}

bool GameSet::sendMessageToClient(int client, string& msg) {
	int writeSize;
	writeSize = send(client, msg.c_str(), msg.length(), SEND_FLAGS);
	if (writeSize == -1) {
		//Error in writing
		cout << "Error writing to client " << client << endl;
		return false;
	}
	return true;
}

GameSet::CommandOption GameSet::getLastCommand() const {
	return lastCommand;
}

int GameSet::getLastCommandResult() const {
	return lastCommandResult;
}

int GameSet::clientExists(int client) {
	for (map<int, int>::iterator it = matchClientMap.begin();
		 it != matchClientMap.end(); ++it) {
		if (it->first == client) {
			return it->second;
		}
	}
	return -1;
}
