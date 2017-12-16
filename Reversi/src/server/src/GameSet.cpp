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
	noAvailableSlotErrorMessage = string("-8");
}

GameSet::~GameSet() {
	//Nothing right now
}

void GameSet::debugMessage(int clientSocket, vector<string> args) {
	string toSend = "";
	char *toStringResult;
	if (args.size() == 0) {
		toSend.append("Last Command: ");
		toStringResult = myToString(lastCommand);
		toSend.append(toStringResult);
		delete[] toStringResult;
		toSend.append("\n");
		toSend.append("Last Result: ");
		toStringResult = myToString(lastCommandResult);
		toSend.append(toStringResult);
		delete[] toStringResult;
		toSend.append("\n");
		sendMessageToClient(clientSocket, toSend);
		lastCommand = GameSet::Debug;
		lastCommandResult = NO_ERROR_RESULT;
		return;
	} else {
		if (args[0] == "find" && args.size() >= 2) {
			for (int i = 0; i < MAX_GAMES; i++) {
				if (matches[i].getGameName() == args[1]) {
					toSend.append("Game ");
					toSend.append(args[1]);
					toSend.append(":\n");
					toSend.append("Status: ");
					toStringResult = myToString(matches[i].getStatus());
					toSend.append(toStringResult);
					delete[] toStringResult;
					toSend.append("Client A: ");
					toStringResult = myToString(matches[i].getClientA());
					toSend.append(toStringResult);
					delete[] toStringResult;
					toSend.append("\n");
					toSend.append("Client B: ");
					toStringResult = myToString(matches[i].getClientB());
					toSend.append(toStringResult);
					sendMessageToClient(clientSocket, toSend);
					lastCommand = GameSet::Debug;
					lastCommandResult = NO_ERROR_RESULT;
					return;
				}
			}
			toSend.append("Game wasn't found");
			sendMessageToClient(clientSocket, toSend);
			lastCommand = GameSet::Debug;
			lastCommandResult = ERROR_GAME_DOES_NOT_EXIST_RESULT;
			return;
		}
	}
	toSend.append("Invalid args");
	sendMessageToClient(clientSocket, toSend);
	lastCommand = GameSet::Debug;
	lastCommandResult = ERROR_NO_ARGS_RESULT;
}

void GameSet::startNewMatch(int clientASocket, vector<string> args) {
	lastCommand = GameSet::Start;

	if (args.size() < 1) {
		lastCommandResult = ERROR_NO_ARGS_RESULT;
		sendMessageToClient(clientASocket, noArgsErrorMessage);
		return;
	}

	GameInfo *availableGame;
	bool foundAvailable = false;

	for (int i = 0; i < MAX_GAMES; i++) {
		if (matches[i].getGameName() == args[0]) {
			lastCommandResult = ERROR_GAME_EXISTS_RESULT;
			sendMessageToClient(clientASocket, gameExistsErrorMessage);
			return;
		} else if (!foundAvailable && matches[i].getStatus() == GameInfo::ReadyForMatch) {
			availableGame = &matches[i];
			foundAvailable = true;
		}
	}

	if (!foundAvailable) {
		lastCommandResult = ERROR_NO_AVAILABLE_SLOT_RESULT;
		sendMessageToClient(clientASocket, noAvailableSlotErrorMessage);
		return;
	}

	availableGame->setClientA(clientASocket);
	availableGame->setGameName(args[0]);
	availableGame->setStatus(GameInfo::XWaiting);

	lastCommandResult = NO_ERROR_RESULT;
	sendMessageToClient(clientASocket, noErrorMessage);
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
