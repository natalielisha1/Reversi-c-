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
#include <pthread.h>

#include "Command.h"
#include "DebugCommand.h"
#include "StartMatchCommand.h"
#include "ListGamesCommand.h"
#include "JoinCommand.h"
#include "PlayCommand.h"
#include "CloseCommand.h"

class CommandsManager {
public:
	static void initialize();

	static CommandsManager *getInstance();

	static void deleteInstance();

	CommandResult executeCommand(int sender, std::string command, std::vector<std::string> args);

private:
	static CommandsManager *theInstance;
	static pthread_mutex_t lock;

	CommandsManager();
	~CommandsManager();

	std::map<std::string, Command *> commandsMap;
};

#endif /* COMMANDSMANAGER_H_ */
