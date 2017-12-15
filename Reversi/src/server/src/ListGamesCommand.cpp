/*
 * ListGamesCommand.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#include "ListGamesCommand.h"

using namespace std;

ListGamesCommand::ListGamesCommand(GameSet &info): info(info) {
	//Nothing right now
}

ListGamesCommand::~ListGamesCommand() {
	//Nothing right now
}

void ListGamesCommand::execute(int sender, vector<string> args) {
	info.listMatches(sender);
}
