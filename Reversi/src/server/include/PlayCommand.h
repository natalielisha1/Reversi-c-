/*
 * PlayCommand.h
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#ifndef PLAYCOMMAND_H_
#define PLAYCOMMAND_H_

#include "Command.h"
#include "GameInfo.h"

#include <vector>
#include <string>

class PlayCommand: public Command {
public:
	PlayCommand(GameInfo& info, int senderSocket);
	virtual ~PlayCommand();

	virtual void execute(std::vector<std::string> args);

private:
	GameInfo& info;
	int sender;
};

#endif /* PLAYCOMMAND_H_ */
