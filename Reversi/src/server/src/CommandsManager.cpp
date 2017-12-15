/*
 * CommandsManager.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#include "CommandsManager.h"

using namespace std;

CommandsManager::CommandsManager(GameSet& info) {
	commandsMap["debug"] = new DebugCommand(info);
	commandsMap["start"] = new StartMatchCommand(info);
	commandsMap["list_games"] = new ListGamesCommand(info);
	commandsMap["join"] = new JoinCommand(info);
	commandsMap["play"] = new PlayCommand(info);
	commandsMap["close"] = new CloseCommand(info);
}

CommandsManager::~CommandsManager() {
	delete commandsMap["debug"];
	delete commandsMap["start"];
	delete commandsMap["list_games"];
	delete commandsMap["join"];
	delete commandsMap["play"];
	delete commandsMap["close"];
}

void CommandsManager::executeCommand(int sender, string command, vector<string> args) {
	Command *currCommand = commandsMap[command];
	currCommand->execute(sender, args);
}
