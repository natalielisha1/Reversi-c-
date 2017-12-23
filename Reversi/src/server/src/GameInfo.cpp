/*
 * GameInfo.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#include "GameInfo.h"

using namespace std;

GameInfo::GameInfo(): clientA(-1), clientB(-1),
					  gameName(""), status(GameInfo::ReadyForMatch),
					  interrupt(false) {
	pthread_mutex_init(&statusMutex, NULL);
	pthread_mutex_init(&interruptMutex, NULL);
	pthread_mutex_init(&nameMutex, NULL);
	pthread_mutex_init(&clientAMutex, NULL);
	pthread_mutex_init(&clientBMutex, NULL);

}

GameInfo::~GameInfo() {
	//Nothing right now
}

int GameInfo::getClientA() {
	pthread_mutex_lock(&clientAMutex);
	int toReturn = clientA;
	pthread_mutex_unlock(&clientAMutex);
	return toReturn;
}

void GameInfo::setClientA(int newClient) {
	pthread_mutex_lock(&clientAMutex);
	this->clientA = newClient;
	pthread_mutex_unlock(&clientAMutex);
}

int GameInfo::getClientB() {
	pthread_mutex_lock(&clientBMutex);
	int toReturn = clientB;
	pthread_mutex_unlock(&clientBMutex);
	return toReturn;
}

void GameInfo::setClientB(int newClient) {
	pthread_mutex_lock(&clientBMutex);
	this->clientB = newClient;
	pthread_mutex_unlock(&clientBMutex);
}

const string& GameInfo::getGameName() {
	pthread_mutex_lock(&nameMutex);
	string& name = gameName;
	pthread_mutex_unlock(&nameMutex);
	return name;
}

void GameInfo::setGameName(const std::string& name) {
	pthread_mutex_lock(&nameMutex);
	this->gameName = name;
	pthread_mutex_unlock(&nameMutex);
}

GameInfo::MatchStatus GameInfo::getStatus() {
	pthread_mutex_lock(&statusMutex);
	GameInfo::MatchStatus toReturn = status;
	pthread_mutex_unlock(&statusMutex);
	return toReturn;
}

void GameInfo::setStatus(GameInfo::MatchStatus newStatus) {
	pthread_mutex_lock(&statusMutex);
	this->status = newStatus;
	pthread_mutex_unlock(&statusMutex);
}

bool GameInfo::clientInMatch(int client) {
	pthread_mutex_lock(&clientAMutex);
	pthread_mutex_lock(&clientBMutex);
	bool toReturn = ((clientA == client) || (clientB == client));
	pthread_mutex_unlock(&clientAMutex);
	pthread_mutex_unlock(&clientBMutex);
	return toReturn;
}

int GameInfo::getOtherClient(int firstClient) {
	pthread_mutex_lock(&clientAMutex);
	pthread_mutex_lock(&clientBMutex);
	int toReturn;

	if (firstClient == clientA) {
		toReturn = clientB;
	} else if (firstClient == clientB) {
		toReturn = clientA;
	} else {
		toReturn = -1;
	}

	pthread_mutex_unlock(&clientAMutex);
	pthread_mutex_unlock(&clientBMutex);
	return toReturn;
}

/*
pthread_mutex_t GameInfo::getStatusMutex() const {
	return statusMutex;
}
*/

void GameInfo::setInterrupt(bool interrupt) {
	pthread_mutex_lock(&interruptMutex);
	this->interrupt = interrupt;
	pthread_mutex_unlock(&interruptMutex);
}

bool GameInfo::getInterrupt() {
	pthread_mutex_lock(&interruptMutex);
	bool toReturn = interrupt;
	pthread_mutex_unlock(&interruptMutex);
	return toReturn;
}
