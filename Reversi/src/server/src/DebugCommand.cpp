/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex7
 **************************************/
#include "DebugCommand.h"

using namespace std;

/***************************************
 * Function Name: DebugCommad (Constructor)
 * The Input: refernce of a game set
 * The Output: instance of a debug command
 * The Function Operation: currently nothing
 **************************************/
DebugCommand::DebugCommand() {
	games = GameSet::getInstance();
}

/***************************************
 * Function Name: DebugCommad (Destructor)
 * The Input: no input
 * The Output: no output
 * The Function Operation: currently nothing
 **************************************/
DebugCommand::~DebugCommand() {
	//Nothing right now
}

/***************************************
 * Function Name: execute
 * The Input: id of a client's socket and
 * a vector of arguments
 * The Output: no output
 * The Function Operation: executing the debug command.
 * if the game exists, the "debug" command returns its
 * state, otherwise it returns an error
 **************************************/
CommandResult DebugCommand::execute(int sender, vector<string> args) {
	return games->debugMessage(sender, args);
}
