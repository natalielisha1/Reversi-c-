/*
 * JoinCommand.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#include "JoinCommand.h"

using namespace std;

JoinCommand::JoinCommand(GameInfo &info, int senderSocket): info(info),
		  	  	  	  	  	  	  	  	  	  	  	  	  	sender(senderSocket) {
}

JoinCommand::~JoinCommand() {
	//Nothing right now
}

void JoinCommand::execute(vector<string> args) {
	string msg = "join - Not Implemented Yet..";
	send(sender, msg.c_str(), msg.length(), SEND_FLAGS);
}
