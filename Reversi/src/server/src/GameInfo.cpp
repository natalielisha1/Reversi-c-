/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex5
 **************************************/

#include "GameInfo.h"

using namespace std;

/***************************************
 * Function Name: GameInfo (Constructor)
 * The Input: no input
 * The Output: instance of GameInfo
 * The Function Operation: initializing the
 * current game information
 **************************************/
GameInfo::GameInfo(): clientA(-1), clientB(-1),
					  gameName(""), status(GameInfo::ReadyForMatch),
					  interrupt(false) {
	pthread_mutex_init(&statusMutex, NULL);
	pthread_mutex_init(&interruptMutex, NULL);
	pthread_mutex_init(&nameMutex, NULL);
	pthread_mutex_init(&clientAMutex, NULL);
	pthread_mutex_init(&clientBMutex, NULL);
}

/***************************************
 * Function Name: ~GameInfo (Destructor)
 * The Input: no input
 * The Output: no output
 * The Function Operation: currently nothing
 **************************************/
GameInfo::~GameInfo() {
	//Nothing right now
}

/***************************************
 * Function Name: getClientA
 * The Input: no input
 * The Output: socket id
 * The Function Operation: returning the
 * socket's id of clientA
 **************************************/
int GameInfo::getClientA() {
	pthread_mutex_lock(&clientAMutex);
	int toReturn = clientA;
	pthread_mutex_unlock(&clientAMutex);
	return toReturn;
}

/***************************************
 * Function Name: setClientA
 * The Input: new client's socket id
 * The Output: no output
 * The Function Operation: updating current
 * clientA's socket id with the given socket id
 **************************************/
void GameInfo::setClientA(int newClient) {
	pthread_mutex_lock(&clientAMutex);
	this->clientA = newClient;
	pthread_mutex_unlock(&clientAMutex);
}

/***************************************
 * Function Name: getClientB
 * The Input: no input
 * The Output: socket's id
 * The Function Operation: returning the
 * socket's id of clientB
 **************************************/
int GameInfo::getClientB() {
	pthread_mutex_lock(&clientBMutex);
	int toReturn = clientB;
	pthread_mutex_unlock(&clientBMutex);
	return toReturn;
}

/***************************************
 * Function Name: setClientB
 * The Input: new client's socket id
 * The Output: no output
 * The Function Operation: updating current
 * clientB's socket id with the given socket id
 **************************************/
void GameInfo::setClientB(int newClient) {
	pthread_mutex_lock(&clientBMutex);
	this->clientB = newClient;
	pthread_mutex_unlock(&clientBMutex);
}

/***************************************
 * Function Name: getGameName
 * The Input: no input
 * The Output: a reference to a string (that
 * contains the name of the function)
 * The Function Operation: returning the name
 * of the current game
 **************************************/
const string& GameInfo::getGameName() {
	pthread_mutex_lock(&nameMutex);
	string& name = gameName;
	pthread_mutex_unlock(&nameMutex);
	return name;
}

/***************************************
 * Function Name: setGameName
 * The Input: a new name for the game
 * The Output: no output
 * The Function Operation: updating current
 * name of the game using a new given name
 **************************************/
void GameInfo::setGameName(const std::string& name) {
	pthread_mutex_lock(&nameMutex);
	this->gameName = name;
	pthread_mutex_unlock(&nameMutex);
}

/***************************************
 * Function Name: getStatus
 * The Input: no input
 * The Output: match status
 * The Function Operation: returning the
 * status of the current game
 **************************************/
GameInfo::MatchStatus GameInfo::getStatus() {
	pthread_mutex_lock(&statusMutex);
	GameInfo::MatchStatus toReturn = status;
	pthread_mutex_unlock(&statusMutex);
	return toReturn;
}

/***************************************
 * Function Name: setStatus
 * The Input: new match status
 * The Output: no output
 * The Function Operation: updating current
 * status with a given match status
 **************************************/
void GameInfo::setStatus(GameInfo::MatchStatus newStatus) {
	pthread_mutex_lock(&statusMutex);
	this->status = newStatus;
	pthread_mutex_unlock(&statusMutex);
}

/***************************************
 * Function Name: clientInMatch
 * The Input: client's socket id
 * The Output: true if the given client is
 * in the current match, otherwise false
 * The Function Operation: checking if the given
 * client is in the current match
 **************************************/
bool GameInfo::clientInMatch(int client) {
	pthread_mutex_lock(&clientAMutex);
	pthread_mutex_lock(&clientBMutex);
	bool toReturn = ((clientA == client) || (clientB == client));
	pthread_mutex_unlock(&clientAMutex);
	pthread_mutex_unlock(&clientBMutex);
	return toReturn;
}

/***************************************
 * Function Name: getOtherClient
 * The Input: the socket id of the first client
 * The Output: the socket id of the second client
 * The Function Operation: returning the socket id
 * of the other client in the game
 **************************************/
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

/***************************************
 * Function Name: setInterrupt
 * The Input: true or false (boolean)
 * The Output: no output
 * The Function Operation: updating the value
 * of the interrupt member of the class according
 * the given boolean
 **************************************/
void GameInfo::setInterrupt(bool interrupt) {
	pthread_mutex_lock(&interruptMutex);
	this->interrupt = interrupt;
	pthread_mutex_unlock(&interruptMutex);
}


/***************************************
 * Function Name: getInterrupt
 * The Input: no input
 * The Output: boolean value
 * The Function Operation: returning the value
 * of the interrupt member of the class
 **************************************/
bool GameInfo::getInterrupt() {
	pthread_mutex_lock(&interruptMutex);
	bool toReturn = interrupt;
	pthread_mutex_unlock(&interruptMutex);
	return toReturn;
}
