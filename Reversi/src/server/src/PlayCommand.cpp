/*
 * PlayCommand.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#include "PlayCommand.h"

using namespace std;

PlayCommand::PlayCommand(GameSet &info): info(info) {
	//Nothing right now
}

PlayCommand::~PlayCommand() {
	//Nothing right now
}

void PlayCommand::execute(int sender, vector<string> args) {
	if (args.size() == 2) {
		info.playMatch(sender, args[0], args[1]);
	} else if (args.size() == 1) {
		info.playMatch(sender, args[0]);
	}
}
