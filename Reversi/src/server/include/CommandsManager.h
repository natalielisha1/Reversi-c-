/*
 * CommandsManager.h
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#ifndef COMMANDSMANAGER_H_
#define COMMANDSMANAGER_H_

#include <map>
#include <string>
#include <vector>

#include "Command.h"
#include "DebugCommand.h"
#include "StartMatchCommand.h"
#include "ListGamesCommand.h"
#include "JoinCommand.h"
#include "PlayCommand.h"
#include "CloseCommand.h"

#include "GameSet.h"

class CommandsManager {
public:
	CommandsManager(GameSet& info);
	~CommandsManager();

	void executeCommand(int sender, std::string command, std::vector<std::string> args);
private:
	std::map<std::string, Command *> commandsMap;
};

#endif /* COMMANDSMANAGER_H_ */
