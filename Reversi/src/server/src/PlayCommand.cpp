/*
 * PlayCommand.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#include "PlayCommand.h"

using namespace std;

PlayCommand::PlayCommand(GameInfo &info, int senderSocket): info(info),
		  	  	  	  	  	  	  	  	  	  	  	  	  	sender(senderSocket) {
}

PlayCommand::~PlayCommand() {
	//Nothing right now
}

void PlayCommand::execute(vector<string> args) {
	string msg = "play - Not Implemented Yet..";
	send(sender, msg.c_str(), msg.length(), SEND_FLAGS);
}
