/*
 * StartMatchCommand.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#include "StartMatchCommand.h"

using namespace std;

StartMatchCommand::StartMatchCommand(GameInfo &info, int senderSocket): info(info),
		  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	sender(senderSocket) {
}

StartMatchCommand::~StartMatchCommand() {
	//Nothing right now
}

void StartMatchCommand::execute(vector<string> args) {
	string msg = "start - Not Implemented Yet..";
	send(sender, msg.c_str(), msg.length(), SEND_FLAGS);
}
