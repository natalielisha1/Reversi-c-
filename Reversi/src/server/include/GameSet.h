/*
 * GameSet.h
 *
 *  Created on: Dec 15, 2017
 *      Author: ofek286
 */

#ifndef GAMESET_H_
#define GAMESET_H_

#include "GameInfo.h"

#include <string>
#include <map>
#include <sys/socket.h>
#include <iostream>

#define MAX_GAMES 5

#define SEND_FLAGS 0

class GameSet {
public:
	enum CommandOption {Debug, Start, Join, Play, Close, List};

	GameSet();
	~GameSet();

	void debugMessage(int clientSocket);

	void startNewMatch(int clientASocket, std::string matchName);

	void joinMatch(int clientBSocket, std::string matchName);

	void playMatch(int senderClient, std::string xLoc, std::string yLoc);

	void playMatch(int senderClient, std::string noMove);

	void closeMatch(int senderClient);

	void listMatches(int senderClient);

	void interruptMatches();

	GameSet::CommandOption getLastCommand() const;

	int getLastCommandResult() const;

private:
	GameInfo matches[5];
	std::map<int, int> matchClientMap;
	GameSet::CommandOption lastCommand;
	int lastCommandResult;

	bool sendMessageToClient(int client, std::string& msg);

	int clientExists(int client);
};

#endif /* GAMESET_H_ */
