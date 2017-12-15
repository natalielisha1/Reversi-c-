/*
 * GameSet.cpp
 *
 *  Created on: Dec 15, 2017
 *      Author: ofek286
 */

#include "GameSet.h"

using namespace std;

GameSet::GameSet(): lastCommand(GameSet::Debug), lastCommandResult(-1) {
	//Nothing right now
}

GameSet::~GameSet() {
	//Nothing right now
}

void GameSet::debugMessage(int clientSocket) {

}

void GameSet::startNewMatch(int clientASocket, string matchName) {
}

void GameSet::joinMatch(int clientBSocket, string matchName) {
}

void GameSet::playMatch(int senderClient, string xLoc, string yLoc) {
}

void GameSet::playMatch(int senderClient, string noMove) {
	string toCompare = "NoMove";
	int currGameIndex = clientExists(senderClient);
	if (currGameIndex == -1) {
		return;
	}
	GameInfo currGame = matches[currGameIndex];
	if (noMove == toCompare) {
		int otherClient = currGame.getOtherClient(senderClient);
		sendMessageToClient(otherClient, noMove);
	}
}

void GameSet::closeMatch(int senderClient) {
}

void GameSet::listMatches(int senderClient) {
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
