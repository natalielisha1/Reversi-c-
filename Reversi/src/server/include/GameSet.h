/*
 * GameSet.h
 *
 *  Created on: Dec 15, 2017
 *      Author: ofek286
 */

#ifndef GAMESET_H_
#define GAMESET_H_

#include "GameInfo.h"
#include "ToolsForStrings.h"

#include <string>
#include <map>
#include <sys/socket.h>
#include <iostream>
#include <vector>

//#define MAX_GAMES 5

#define SEND_FLAGS 0

//Predefined error results
#define NO_ERROR_RESULT 1
#define ERROR_GAME_EXISTS_RESULT -1
#define ERROR_NO_ARGS_RESULT -2
#define ERROR_INVALID_CLIENT_RESULT -3
#define ERROR_GAME_NOT_PLAYING_RESULT -4
#define ERROR_FAKE_NO_MOVE_RESULT -5
#define ERROR_GAME_DOES_NOT_EXIST_RESULT -6
#define ERROR_GAME_FULL_RESULT -7
//#define ERROR_NO_AVAILABLE_SLOT_RESULT -8

class GameSet {
public:
	enum CommandOption {Debug, Start, Join, Play, Close, List};

	GameSet();
	~GameSet();

	void debugMessage(int clientSocket, std::vector<std::string>);

	void startNewMatch(int clientASocket, std::vector<std::string> args);

	void joinMatch(int clientBSocket, std::vector<std::string> args);

	void playMatch(int senderClient, std::string xLoc, std::string yLoc);

	void playMatch(int senderClient, std::string noMove);

	void closeMatch(int senderClient, std::vector<std::string> args);

	void listMatches(int senderClient);

	void interruptMatches();

	GameSet::CommandOption getLastCommand() const;

	int getLastCommandResult() const;

private:
	//GameInfo matches[5];
	std::vector<GameInfo *>matches;
	std::map<int, GameInfo *> matchClientMap;
	GameSet::CommandOption lastCommand;
	int lastCommandResult;

	bool sendMessageToClient(int client, std::string& msg);

	GameInfo *clientExists(int client);

	//Regular messages
	std::string firstPlayerMessage;
	std::string secondPlayerMessage;

	//Error messages
	std::string noErrorMessage;
	std::string gameExistsErrorMessage;
	std::string noArgsErrorMessage;
	std::string gameFullErrorMessage;
	std::string gameDoesNotExistErrorMessage;
	//std::string noAvailableSlotErrorMessage;
};

#endif /* GAMESET_H_ */
