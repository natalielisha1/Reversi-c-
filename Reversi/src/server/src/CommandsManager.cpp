/*
 * CommandsManager.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#include "CommandsManager.h"

using namespace std;

CommandsManager::CommandsManager(GameInfo& info, int senderSocket) {
	commandsMap["debug"] = new DebugCommand(info, senderSocket);
	commandsMap["start"] = new StartMatchCommand(info, senderSocket);
	commandsMap["list_games"] = new ListGamesCommand(info, senderSocket);
	commandsMap["join"] = new JoinCommand(info, senderSocket);
	commandsMap["play"] = new PlayCommand(info, senderSocket);
	commandsMap["close"] = new CloseCommand(info, senderSocket);
}

CommandsManager::~CommandsManager() {
	delete commandsMap["debug"];
	delete commandsMap["start"];
	delete commandsMap["list_games"];
	delete commandsMap["join"];
	delete commandsMap["play"];
	delete commandsMap["close"];
}

void CommandsManager::executeCommand(string command, vector<string> args) {
	Command *currCommand = commandsMap[command];
	currCommand->execute(args);
}
