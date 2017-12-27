/*
 * JoinCommand.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#include "JoinCommand.h"

using namespace std;

/***************************************
 * Function Name: joinCommand (Constructor)
 * The Input: a reference of a game set
 * The Output: joinCommand instance
 * The Function Operation: currently nothing
 **************************************/
JoinCommand::JoinCommand(GameSet &info): info(info) {
	//Nothing right now
}

/***************************************
 * Function Name: ~joinCommand (Destructor)
 * The Input: no input
 * The Output: no ouput
 * The Function Operation: currently nothing
 **************************************/
JoinCommand::~JoinCommand() {
	//Nothing right now
}

/***************************************
 * Function Name: execute
 * The Input: id socket of the sender and a vector
 * of arguments
 * The Output: no ouput
 * The Function Operation: adding the sender (a client)
 * to a match
 **************************************/
void JoinCommand::execute(int sender, vector<string> args) {
	info.joinMatch(sender, args);
}
