/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex7
 **************************************/

#include "CommandsManager.h"

using namespace std;

CommandsManager *CommandsManager::theInstance = NULL;
pthread_mutex_t CommandsManager::lock = PTHREAD_MUTEX_INITIALIZER;

void CommandsManager::initialize() {
	pthread_mutex_init(&lock, NULL);
	GameSet::initialize();
}

CommandsManager *CommandsManager::getInstance() {
	if (theInstance == NULL) {
		pthread_mutex_lock(&lock);
		if (theInstance == NULL) {
			theInstance = new CommandsManager();
		}
		pthread_mutex_unlock(&lock);
	}
	return theInstance;
}

void CommandsManager::deleteInstance() {
	if (theInstance != NULL) {
		pthread_mutex_lock(&lock);
		if (theInstance != NULL) {
			delete theInstance;
			theInstance = NULL;
		}
		pthread_mutex_unlock(&lock);
	}

	GameSet::deleteInstance();
}

/***************************************
 * Function Name: CommandsManager (Constructor)
 * The Input: a reference to a game set object
 * The Output: commands manager instance
 * The Function Operation: initializing the commands
 * manager object
 **************************************/
CommandsManager::CommandsManager() {
	commandsMap["debug"] = new DebugCommand();
	commandsMap["start"] = new StartMatchCommand();
	commandsMap["list_games"] = new ListGamesCommand();
	commandsMap["join"] = new JoinCommand();
	commandsMap["play"] = new PlayCommand();
	commandsMap["close"] = new CloseCommand();
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
CommandResult CommandsManager::executeCommand(int sender, string command, vector<string> args) {
	Command *currCommand = commandsMap[command];
	return currCommand->execute(sender, args);
}
