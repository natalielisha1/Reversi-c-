/*
 * PlayCommand.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#include "PlayCommand.h"

using namespace std;

/***************************************
 * Function Name: PlayCommand (Constructor)
 * The Input: a reference to a game set
 * The Output: instance of PlayCommand
 * The Function Operation: currently nothing
 **************************************/
PlayCommand::PlayCommand(GameSet &info): info(info) {
	//Nothing right now
}

/***************************************
 * Function Name: ~PlayCommand (Destructor)
 * The Input: no input
 * The Output: no output
 * The Function Operation: currently nothing
 **************************************/
PlayCommand::~PlayCommand() {
	//Nothing right now
}

/***************************************
 * Function Name: execute
 * The Input: sender's socket id and a vector
 * of arguments
 * The Output: no output
 * The Function Operation: executing (playing)
 * accordingly to the command
 **************************************/
void PlayCommand::execute(int sender, vector<string> args) {
	if (args.size() == 2) {
		info.playMatch(sender, args[0], args[1]);
	} else if (args.size() == 1) {
		info.playMatch(sender, args[0]);
	}
}
