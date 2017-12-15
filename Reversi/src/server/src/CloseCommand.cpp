/*
 * CloseCommand.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#include "CloseCommand.h"

using namespace std;

CloseCommand::CloseCommand(GameSet &info): info(info) {
	//Nothing right now
}

CloseCommand::~CloseCommand() {
	//Nothing right now
}

void CloseCommand::execute(int sender, vector<string> args) {
	info.closeMatch(sender, args);
}
