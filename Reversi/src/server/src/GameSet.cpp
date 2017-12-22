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
	noErrorMessage = string("OK");
	gameExistsErrorMessage = string("-1");
	noArgsErrorMessage = string("-2");
	gameDoesNotExistErrorMessage = string("-6");
	gameFullErrorMessage = string("-7");
	//noAvailableSlotErrorMessage = string("-8");
}

GameSet::~GameSet() {
	for (vector<GameInfo *>::iterator it = matches.begin(); it != matches.end(); ++it) {
		delete *it;
	}
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
			for (vector<GameInfo *>::iterator it = matches.begin(); it != matches.end(); ++it) {
				if ((*it)->getGameName() == args[1]) {
					toSend.append("Game ");
					toSend.append(args[1]);
					toSend.append(":\n");
					toSend.append("Status: ");
					toStringResult = myToString((*it)->getStatus());
					toSend.append(toStringResult);
					delete[] toStringResult;
					toSend.append("Client A: ");
					toStringResult = myToString((*it)->getClientA());
					toSend.append(toStringResult);
					delete[] toStringResult;
					toSend.append("\n");
					toSend.append("Client B: ");
					toStringResult = myToString((*it)->getClientB());
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

	GameInfo *newGame;

	for (vector<GameInfo *>::iterator it = matches.begin(); it != matches.end(); ++it) {
		if ((*it)->getGameName() == args[0]) {
			lastCommandResult = ERROR_GAME_EXISTS_RESULT;
			sendMessageToClient(clientASocket, gameExistsErrorMessage);
			return;
		}
	}

	newGame = new GameInfo();

	newGame->setClientA(clientASocket);
	newGame->setGameName(args[0]);
	newGame->setStatus(GameInfo::XWaiting);

	matches.push_back(newGame);
	matchClientMap[clientASocket] = newGame;

	lastCommandResult = NO_ERROR_RESULT;
	sendMessageToClient(clientASocket, noErrorMessage);
}

void GameSet::joinMatch(int clientBSocket, vector<string> args) {
	lastCommand = GameSet::Join;

	if (args.size() < 1) {
		lastCommandResult = ERROR_NO_ARGS_RESULT;
		return;
	}
	for (vector<GameInfo *>::iterator it = matches.begin(); it != matches.end(); ++it) {
		if ((*it)->getGameName() == args[0]) {
			if ((*it)->getStatus() != GameInfo::XWaiting) {
				lastCommandResult = ERROR_GAME_FULL_RESULT;
				sendMessageToClient(clientBSocket, gameFullErrorMessage);
				return;
			} else {
				lastCommandResult = NO_ERROR_RESULT;
				int clientASocket = (*it)->getClientA();
				matchClientMap[clientBSocket] = *it;
				(*it)->setClientB(clientBSocket);
				(*it)->setStatus(GameInfo::Playing);
				sendMessageToClient(clientASocket, firstPlayerMessage);
				sendMessageToClient(clientBSocket, secondPlayerMessage);
				return;
			}
		}
	}
	lastCommandResult = ERROR_GAME_DOES_NOT_EXIST_RESULT;
	sendMessageToClient(clientBSocket, gameDoesNotExistErrorMessage);
}

void GameSet::playMatch(int senderClient, string xLoc, string yLoc) {
	lastCommand = GameSet::Play;

	string toSend = string(xLoc);
	toSend.append(", ");
	toSend.append(yLoc);

	GameInfo *currGame = clientExists(senderClient);
	if (currGame == NULL) {
		lastCommandResult = ERROR_INVALID_CLIENT_RESULT;
		return;
	}
	if (currGame->getStatus() != GameInfo::Playing) {
		lastCommandResult = ERROR_GAME_NOT_PLAYING_RESULT;
		return;
	}
	int otherClient = currGame->getOtherClient(senderClient);
	sendMessageToClient(otherClient, toSend);
	lastCommandResult = NO_ERROR_RESULT;
}

void GameSet::playMatch(int senderClient, string noMove) {
	lastCommand = GameSet::Play;

	string toCompare = "NoMove";
	GameInfo *currGame = clientExists(senderClient);
	if (currGame == NULL) {
		lastCommandResult = ERROR_INVALID_CLIENT_RESULT;
		return;
	}
	if (currGame->getStatus() != GameInfo::Playing) {
		lastCommandResult = ERROR_GAME_NOT_PLAYING_RESULT;
		return;
	}
	if (noMove == toCompare) {
		int otherClient = currGame->getOtherClient(senderClient);
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
	for (vector<GameInfo *>::iterator it = matches.begin(); it != matches.end(); ++it) {
		if ((*it)->getGameName() == args[0]) {
			GameInfo *toClose = (*it);
			toClose->setInterrupt(true);
			//TODO: Mutex to wait
			matchClientMap.erase(toClose->getClientA());
			matchClientMap.erase(toClose->getClientB());
			matches.erase(it);
			delete toClose;
			lastCommandResult = NO_ERROR_RESULT;
			return;
		}
	}
	lastCommandResult = ERROR_GAME_DOES_NOT_EXIST_RESULT;
}

void GameSet::listMatches(int senderClient) {
	lastCommand = GameSet::List;
	string toSend = "";
	for (vector<GameInfo *>::iterator it = matches.begin(); it != matches.end(); ++it) {
		if ((*it)->getStatus() == GameInfo::XWaiting) {
			if (toSend != "") {
				toSend.append(",");
			}
			toSend.append((*it)->getGameName());
		}
	}
	sendMessageToClient(senderClient, toSend);
	lastCommandResult = NO_ERROR_RESULT;
}

void GameSet::interruptMatches() {
	for (vector<GameInfo *>::iterator it = matches.begin(); it != matches.end(); ++it) {
		(*it)->setInterrupt(true);
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

GameInfo *GameSet::clientExists(int client) {
	for (map<int, GameInfo *>::iterator it = matchClientMap.begin();
		 it != matchClientMap.end(); ++it) {
		if (it->first == client) {
			return it->second;
		}
	}
	return NULL;
}

GameInfo* GameSet::getGameInfo(int client) {
	//TODO: WRITE
	return NULL;
}
