/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex5
 **************************************/

#include "GameSet.h"

using namespace std;

/***************************************
 * Function Name: GameSet
 * The Input: no input
 * 					  command result
 * The Output: a GameSet instance
 * The Function Operation: initializing
 * the game set
 **************************************/
GameSet::GameSet(): lastCommand(GameSet::Debug), lastCommandResult(-1) {
	//Regular messages init
	firstPlayerMessage = string("1");
	secondPlayerMessage = string("2");
	endGameMessage = string("END");
	noGamesAvailableMessage = string("NONE");

	//Error messages init
	noErrorMessage = string("OK");
	gameExistsErrorMessage = string("-1");
	noArgsErrorMessage = string("-2");
	gameDoesNotExistErrorMessage = string("-6");
	gameFullErrorMessage = string("-7");

	//Mutex initializing
	pthread_mutex_init(&matchesMutex, NULL);
	pthread_mutex_init(&clientMapMutex, NULL);
	pthread_mutex_init(&stringsMutex, NULL);
}

/***************************************
 * Function Name: ~GameSet (Destructor)
 * The Input: no input
 * The Output: no output
 * The Function Operation: deletes every
 * element in the game information vector
 **************************************/
GameSet::~GameSet() {
	for (vector<GameInfo *>::iterator it = matches.begin(); it != matches.end(); ++it) {
		delete *it;
	}
}

/***************************************
 * Function Name: debugMessage
 * The Input: integer that represents the
 * client socket and a vector of strings that
 * contains the arguments
 * The Output: no output
 * The Function Operation: sending debug
 * 			   info to the
 *			   client
 **************************************/
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

/***************************************
 * Function Name: startNewMatch
 * The Input: integer that represents client
 * A's socket and a vector of strings that
 * represents the arguments
 * The Output: no output
 * The Function Operation: starting a new match
 **************************************/
void GameSet::startNewMatch(int clientASocket, vector<string> args) {
	lastCommand = GameSet::Start;

	if (args.size() < 1) {
		lastCommandResult = ERROR_NO_ARGS_RESULT;
		pthread_mutex_lock(&stringsMutex);
		sendMessageToClient(clientASocket, noArgsErrorMessage);
		pthread_mutex_unlock(&stringsMutex);
		return;
	}

	GameInfo *newGame;

	pthread_mutex_lock(&matchesMutex);
	for (vector<GameInfo *>::iterator it = matches.begin(); it != matches.end(); ++it) {
		if ((*it)->getGameName() == args[0]) {
			lastCommandResult = ERROR_GAME_EXISTS_RESULT;
			pthread_mutex_lock(&stringsMutex);
			sendMessageToClient(clientASocket, gameExistsErrorMessage);
			pthread_mutex_unlock(&stringsMutex);
			pthread_mutex_unlock(&matchesMutex);
			return;
		}
	}
	pthread_mutex_unlock(&matchesMutex);

	newGame = new GameInfo();

	newGame->setClientA(clientASocket);
	newGame->setGameName(args[0]);
	newGame->setStatus(GameInfo::XWaiting);

	pthread_mutex_lock(&matchesMutex);
	matches.push_back(newGame);
	pthread_mutex_unlock(&matchesMutex);

	pthread_mutex_lock(&clientMapMutex);
	matchClientMap[clientASocket] = newGame;
	pthread_mutex_unlock(&clientMapMutex);

	lastCommandResult = NO_ERROR_RESULT;
	pthread_mutex_lock(&stringsMutex);
	sendMessageToClient(clientASocket, noErrorMessage);
	pthread_mutex_unlock(&stringsMutex);
}

/***************************************
 * Function Name: joinMatch
 * The Input: a socket id of the second client
 * (the client who wants to join) and vector of
 * arguments
 * The Output: no output
 * The Function Operation: adding a new client
 * to the match
 **************************************/
void GameSet::joinMatch(int clientBSocket, vector<string> args) {
	lastCommand = GameSet::Join;

	if (args.size() < 1) {
		lastCommandResult = ERROR_NO_ARGS_RESULT;
		return;
	}
	pthread_mutex_lock(&matchesMutex);
	for (vector<GameInfo *>::iterator it = matches.begin(); it != matches.end(); ++it) {
		if ((*it)->getGameName() == args[0]) {
			if ((*it)->getStatus() != GameInfo::XWaiting) {
				lastCommandResult = ERROR_GAME_FULL_RESULT;
				pthread_mutex_lock(&stringsMutex);
				sendMessageToClient(clientBSocket, gameFullErrorMessage);
				pthread_mutex_unlock(&stringsMutex);
				pthread_mutex_unlock(&matchesMutex);
				return;
			} else {
				lastCommandResult = NO_ERROR_RESULT;
				int clientASocket = (*it)->getClientA();
				matchClientMap[clientBSocket] = *it;
				(*it)->setClientB(clientBSocket);
				(*it)->setStatus(GameInfo::Playing);
				pthread_mutex_lock(&stringsMutex);
				sendMessageToClient(clientBSocket, noErrorMessage);
				sendMessageToClient(clientASocket, firstPlayerMessage);
				sendMessageToClient(clientBSocket, secondPlayerMessage);
				pthread_mutex_unlock(&stringsMutex);
				pthread_mutex_unlock(&matchesMutex);
				return;
			}
		}
	}
	pthread_mutex_unlock(&matchesMutex);
	lastCommandResult = ERROR_GAME_DOES_NOT_EXIST_RESULT;
	pthread_mutex_lock(&stringsMutex);
	sendMessageToClient(clientBSocket, gameDoesNotExistErrorMessage);
	pthread_mutex_unlock(&stringsMutex);
}

/***************************************
 * Function Name: playMatch
 * The Input: an id of the socket of the
 * client, the x rate of the location of
 * the move and the y rate of the same
 * location
 * The Output: no output
 * The Function Operation: playing the match
 * using the location of the intended move
 **************************************/
void GameSet::playMatch(int senderClient, string xLoc, string yLoc) {
	lastCommand = GameSet::Play;

	string toSend = string(xLoc);
	toSend.append(", ");
	toSend.append(yLoc);

	GameInfo *currGame = getGameInfo(senderClient);
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

/***************************************
 * Function Name: playMatch
 * The Input: the id socket of the sender client
 * and a string of "no move"
 * The Output: no output
 * The Function Operation: "play the match"
 * in case where there is no move- check
 * if there's indeed no move and send an error
 * and/or a message accordingly
 **************************************/
void GameSet::playMatch(int senderClient, string noMove) {
	lastCommand = GameSet::Play;

	string toCompare = "NoMove";
	GameInfo *currGame = getGameInfo(senderClient);
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

/***************************************
 * Function Name: closeMatch
 * The Input: a socket id of the sender client
 * and vector of arguments
 * The Output: no output
 * The Function Operation: closing the match
 **************************************/
void GameSet::closeMatch(int senderClient, vector<string> args) {
	lastCommand = GameSet::Close;

	if (args.size() < 1) {
		lastCommandResult = ERROR_NO_ARGS_RESULT;
		return;
	}
	pthread_mutex_lock(&matchesMutex);
	for (vector<GameInfo *>::iterator it = matches.begin(); it != matches.end(); ++it) {
		if ((*it)->getGameName() == args[0]) {
			GameInfo *toClose = (*it);
			int other = toClose->getOtherClient(senderClient);
			pthread_mutex_lock(&stringsMutex);
			sendMessageToClient(other, endGameMessage);
			pthread_mutex_unlock(&stringsMutex);
			toClose->setInterrupt(true);
			pthread_mutex_lock(&clientMapMutex);
			matchClientMap.erase(toClose->getClientA());
			matchClientMap.erase(toClose->getClientB());
			pthread_mutex_unlock(&clientMapMutex);
			close(toClose->getClientA());
			close(toClose->getClientB());
			//matches.erase(it);
			//delete toClose;
			lastCommandResult = NO_ERROR_RESULT;
			pthread_mutex_unlock(&matchesMutex);
			return;
		}
	}
	pthread_mutex_unlock(&matchesMutex);
	lastCommandResult = ERROR_GAME_DOES_NOT_EXIST_RESULT;
}

/***************************************
 * Function Name: listMatches
 * The Input: a socket id of the sender client
 * The Output: no output
 * The Function Operation: listing the names of
 * the matches that played
 **************************************/
void GameSet::listMatches(int senderClient) {
	lastCommand = GameSet::List;
	string toSend = "";
	pthread_mutex_lock(&matchesMutex);
	for (vector<GameInfo *>::iterator it = matches.begin(); it != matches.end(); ++it) {
		if ((*it)->getStatus() == GameInfo::XWaiting) {
			if (toSend != "") {
				toSend.append(",");
			}
			toSend.append((*it)->getGameName());
		}
	}
	pthread_mutex_unlock(&matchesMutex);
	if (toSend == "") {
		toSend = noGamesAvailableMessage;
	}
	sendMessageToClient(senderClient, toSend);
	lastCommandResult = NO_ERROR_RESULT;
}

/***************************************
 * Function Name: interruptMatches
 * The Input: no input
 * The Output: no output
 * The Function Operation: interrupting
 * each match in game
 **************************************/
void GameSet::interruptMatches() {
	pthread_mutex_lock(&matchesMutex);
	for (vector<GameInfo *>::iterator it = matches.begin(); it != matches.end(); ++it) {
		(*it)->setInterrupt(true);
	}
	pthread_mutex_unlock(&matchesMutex);
}

/***************************************
 * Function Name: removeGame
 * The Input: the game information of the current
 * game
 * The Output: true if the removal has succeeded,
 * otherwise false
 * The Function Operation: removing the current game
 **************************************/
bool GameSet::removeGame(GameInfo *currGame) {
	//GameInfo *currGame = getGameInfo(client);
	if (currGame == NULL) {
		return false;
	} else {
		GameInfo *temp;
		temp = getGameInfo(currGame->getClientA());
		if (temp != NULL) {
			int clientA = currGame->getClientA();
			int clientB = currGame->getClientB();

			pthread_mutex_lock(&stringsMutex);
			sendMessageToClient(clientA, endGameMessage);
			sendMessageToClient(clientB, endGameMessage);
			pthread_mutex_unlock(&stringsMutex);

			pthread_mutex_lock(&clientMapMutex);
			matchClientMap.erase(clientA);
			matchClientMap.erase(clientB);
			pthread_mutex_unlock(&clientMapMutex);

			close(clientA);
			close(clientB);
		}

		pthread_mutex_lock(&matchesMutex);
		removeFromVector(&matches, currGame);
		pthread_mutex_unlock(&matchesMutex);

		delete currGame;
		return true;
	}
}

/***************************************
 * Function Name: sendMessageToClient
 * The Input: the id of a client and a reference
 * to the message that need to be sent to that client
 * The Output: true if the process succeed,
 * otherwise false
 * The Function Operation: sending the
 *			   message to
 *		           the client
 **************************************/
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

/***************************************
 * Function Name: getLastCommand
 * The Input: no input
 * The Output: command option
 * The Function Operation: getting
 * the last command sent to the server
 **************************************/
GameSet::CommandOption GameSet::getLastCommand() const {
	return lastCommand;
}

/***************************************
 * Function Name: getLastCommandResult
 * The Input: no input
 * The Output: command result
 * The Function Operation: getting
 * the last command result in the server
 **************************************/
int GameSet::getLastCommandResult() const {
	return lastCommandResult;
}

/***************************************
 * Function Name: getGameInfo
 * The Input: id of a client's socket
 * The Output: a pointer of a game information
 * The Function Operation: returning the game
 * information according to the given client
 **************************************/
GameInfo *GameSet::getGameInfo(int client) {
	GameInfo *toReturn = NULL;
	pthread_mutex_lock(&clientMapMutex);
	for (map<int, GameInfo *>::iterator it = matchClientMap.begin();
		 it != matchClientMap.end(); ++it) {
		if (it->first == client) {
			toReturn = it->second;
		}
	}
	pthread_mutex_unlock(&clientMapMutex);
	return toReturn;
}
