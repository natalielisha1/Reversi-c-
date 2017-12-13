/*
 * CloseCommand.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#include "CloseCommand.h"

using namespace std;

CloseCommand::CloseCommand(GameInfo &info, int senderSocket): info(info),
		  	  	  	  	  	  	  	  	  	  	  	  	  	  sender(senderSocket) {
}

CloseCommand::~CloseCommand() {
	//Nothing right now
}

void CloseCommand::execute(vector<string> args) {
	string msg = "close - Not Implemented Yet..";
	send(sender, msg.c_str(), msg.length(), SEND_FLAGS);
}
