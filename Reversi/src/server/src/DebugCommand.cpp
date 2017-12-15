/*
 * DebugCommand.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#include "DebugCommand.h"

using namespace std;

DebugCommand::DebugCommand(GameSet &info): info(info) {
	//Nothing right now
}

DebugCommand::~DebugCommand() {
	//Nothing right now
}

void DebugCommand::execute(int sender, vector<string> args) {
	info.debugMessage(sender, args);
}
