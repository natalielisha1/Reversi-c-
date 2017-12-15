/*
 * StartMatchCommand.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#include "StartMatchCommand.h"

using namespace std;

StartMatchCommand::StartMatchCommand(GameSet &info): info(info) {
	//Nothing right now
}

StartMatchCommand::~StartMatchCommand() {
	//Nothing right now
}

void StartMatchCommand::execute(int sender, vector<string> args) {
	info.startNewMatch(sender, args);
}
