/*
 * StartMatchCommand.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#include "StartMatchCommand.h"

using namespace std;

/***************************************
 * Function Name: StartMatchCommand (Constructor)
 * The Input: reference to a game set
 * The Output: instance of StartMatchCommand
 * The Function Operation: currently nothing
 **************************************/
StartMatchCommand::StartMatchCommand(GameSet &info): info(info) {
	//Nothing right now
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
void StartMatchCommand::execute(int sender, vector<string> args) {
	info.startNewMatch(sender, args);
}
