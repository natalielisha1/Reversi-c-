/*
 * CloseCommand.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#include "CloseCommand.h"

using namespace std;

/***************************************
 * Function Name: CloseCommand (Constructor)
 * The Input: reference to a gameSet
 * The Output: a closeCommand instance
 * The Function Operation: currently nothing
 **************************************/
CloseCommand::CloseCommand(GameSet &info): info(info) {
	//Nothing right now
}

/***************************************
 * Function Name: CloseCommand (Destructor)
 * The Input: no input
 * The Output: no output
 * The Function Operation: currently nothing
 **************************************/
CloseCommand::~CloseCommand() {
	//Nothing right now
}

/***************************************
 * Function Name: execute
 * The Input:
 * The Output: no output
 * The Function Operation:
 **************************************/
void CloseCommand::execute(int sender, vector<string> args) {
	info.closeMatch(sender, args);
}
