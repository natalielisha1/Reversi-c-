/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex5
 **************************************/

#include "CommandsManager.h"

using namespace std;

/***************************************
 * Function Name: CommandsManager (Constructor)
 * The Input: a reference to a game set object
 * The Output: commands manager instance
 * The Function Operation: initializing the commands
 * manager object
 **************************************/
CommandsManager::CommandsManager(GameSet& info) {
	commandsMap["debug"] = new DebugCommand(info);
	commandsMap["start"] = new StartMatchCommand(info);
	commandsMap["list_games"] = new ListGamesCommand(info);
	commandsMap["join"] = new JoinCommand(info);
	commandsMap["play"] = new PlayCommand(info);
	commandsMap["close"] = new CloseCommand(info);
}

/***************************************
 * Function Name: ~CommandsManager (Destructor)
 * The Input: no input
 * The Output: no output
 * The Function Operation: destructing
 * the commands manager object
 **************************************/
CommandsManager::~CommandsManager() {
	delete commandsMap["debug"];
	delete commandsMap["start"];
	delete commandsMap["list_games"];
	delete commandsMap["join"];
	delete commandsMap["play"];
	delete commandsMap["close"];
}

/***************************************
 * Function Name: executeCommand
 * The Input: sender's socket's id, a command
 * and a vector of arguments
 * The Output: no output
 * The Function Operation: executing the
 * given command
 **************************************/
void CommandsManager::executeCommand(int sender, string command, vector<string> args) {
	Command *currCommand = commandsMap[command];
	currCommand->execute(sender, args);
}
