/*
 * ListGamesCommand.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#include "ListGamesCommand.h"

using namespace std;

ListGamesCommand::ListGamesCommand(GameInfo &info, int senderSocket): info(info),
		  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  sender(senderSocket) {
}

ListGamesCommand::~ListGamesCommand() {
	//Nothing right now
}

void ListGamesCommand::execute(vector<string> args) {
	string msg = "list_games - Not Implemented Yet..";
	send(sender, msg.c_str(), msg.length(), SEND_FLAGS);
}
