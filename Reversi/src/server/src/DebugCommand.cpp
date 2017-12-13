/*
 * DebugCommand.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#include "DebugCommand.h"

using namespace std;

DebugCommand::DebugCommand(GameInfo &info, int senderSocket): info(info),
															  sender(senderSocket) {
}

DebugCommand::~DebugCommand() {
	//Nothing right now
}

void DebugCommand::execute(vector<string> args) {
	string msg = "DEBUG - Not Implemented Yet..";
	send(sender, msg.c_str(), msg.length(), SEND_FLAGS);
}
