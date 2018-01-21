/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex5
 **************************************/

#ifndef GAMESET_H_
#define GAMESET_H_

#include "CommandResult.h"
#include "GameInfo.h"
#include "ToolsForStrings.h"
#include "Tools.h"

#include <string>
#include <map>
#include <sys/socket.h>
#include <iostream>
#include <vector>
#include <pthread.h>
#include <unistd.h>
#include <pthread.h>

#define SEND_FLAGS 0

class GameSet {
public:
	static void initialize();

	static GameSet *getInstance();

	static void deleteInstance();

	CommandResult debugMessage(int clientSocket, std::vector<std::string>);

	CommandResult startNewMatch(int clientASocket, std::vector<std::string> args);

	CommandResult joinMatch(int clientBSocket, std::vector<std::string> args);

	CommandResult playMatch(int senderClient, std::string xLoc, std::string yLoc);

	CommandResult playMatch(int senderClient, std::string noMove);

	CommandResult closeMatch(int senderClient, std::vector<std::string> args);

	CommandResult listMatches(int senderClient);

	void interruptMatches();

	CommandResult::CommandOption getLastCommand() const;

	int getLastCommandResult() const;

	GameInfo *getGameInfo(int client);

	bool removeGame(GameInfo *currGame);
private:
	static GameSet *theInstance;
	static pthread_mutex_t lock;

	GameSet();
	~GameSet();

	std::vector<GameInfo *>matches;
	std::map<int, GameInfo *> matchClientMap;

	CommandResult::CommandOption lastCommand;
	int lastCommandResult;

	pthread_mutex_t lastCommandMutex;

	pthread_mutex_t matchesMutex;
	pthread_mutex_t clientMapMutex;
	pthread_mutex_t stringsMutex;

	bool sendMessageToClient(int client, std::string& msg);

	//Regular messages
	std::string firstPlayerMessage;
	std::string secondPlayerMessage;
	std::string endGameMessage;
	std::string noGamesAvailableMessage;

	//Error messages
	std::string noErrorMessage;
	std::string gameExistsErrorMessage;
	std::string noArgsErrorMessage;
	std::string gameFullErrorMessage;
	std::string gameDoesNotExistErrorMessage;
};

#endif /* GAMESET_H_ */
