/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex7
 **************************************/

#include "StartMatchCommand.h"

using namespace std;

/***************************************
 * Function Name: StartMatchCommand (Constructor)
 * The Input: reference to a game set
 * The Output: instance of StartMatchCommand
 * The Function Operation: currently nothing
 **************************************/
StartMatchCommand::StartMatchCommand() {
	games = GameSet::getInstance();
}

/***************************************
 * Function Name: ~StartMatchCommand (Destructor)
 * The Input: no input
 * The Output: no ouput
 * The Function Operation: currently nothing
 **************************************/
StartMatchCommand::~StartMatchCommand() {
	//Nothing right now
}

/***************************************
 * Function Name: execute
 * The Input: socket id of sender and a vector
 * of arguments
 * The Output: no output
 * The Function Operation: starting a new match
 **************************************/
CommandResult StartMatchCommand::execute(int sender, vector<string> args) {
	return games->startNewMatch(sender, args);
}
