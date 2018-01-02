/*
 * DebugCommand.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#include "DebugCommand.h"

using namespace std;

/***************************************
 * Function Name: DebugCommad (Constructor)
 * The Input: refernce of a game set
 * The Output: instance of a debug command
 * The Function Operation: currently nothing
 **************************************/
DebugCommand::DebugCommand(GameSet &info): info(info) {
	//Nothing right now
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
 * if the game exists, it the "debug" command returns it's
 * state, otherwise it returns an error
 **************************************/
void DebugCommand::execute(int sender, vector<string> args) {
	info.debugMessage(sender, args);
}
