/*
 * GameInfo.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#include "GameInfo.h"

GameInfo::GameInfo(): clientA(-1), clientB(-1),
					  gameName(""), status(GameInfo::ReadyForMatch) {
	//Nothing right now

}

GameInfo::~GameInfo() {
	//Nothing right now
}

int GameInfo::getClientA() const {
	return clientA;
}

void GameInfo::setClientA(int clientA) {
	this->clientA = clientA;
}

int GameInfo::getClientB() const {
	return clientB;
}

void GameInfo::setClientB(int clientB) {
	this->clientB = clientB;
}

const std::string& GameInfo::getGameName() const {
	return gameName;
}

void GameInfo::setGameName(const std::string& gameName) {
	this->gameName = gameName;
}

GameInfo::MatchStatus GameInfo::getStatus() const {
	return status;
}

void GameInfo::setStatus(GameInfo::MatchStatus status) {
	this->status = status;
}

bool GameInfo::clientInMatch(int client) const {
	return ((clientA == client) || (clientB == client));
}

int GameInfo::getOtherClient(int firstClient) const {
	if (firstClient == clientA) {
		return clientB;
	} else if (firstClient == clientB) {
		return clientA;
	}
	return -1;
}

pthread_mutex_t GameInfo::getStatusMutex() const {
	return statusMutex;
}
