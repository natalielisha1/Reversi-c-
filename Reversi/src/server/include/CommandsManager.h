/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex5
 **************************************/

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
