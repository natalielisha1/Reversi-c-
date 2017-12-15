/*
 * JoinCommand.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#include "JoinCommand.h"

using namespace std;

JoinCommand::JoinCommand(GameSet &info): info(info) {
	//Nothing right now
}

JoinCommand::~JoinCommand() {
	//Nothing right now
}

void JoinCommand::execute(int sender, vector<string> args) {
	info.joinMatch(sender, args);
}
