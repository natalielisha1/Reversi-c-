/*
 * StartMatchCommand.h
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#ifndef STARTMATCHCOMMAND_H_
#define STARTMATCHCOMMAND_H_

#include "Command.h"
#include "GameInfo.h"

#include <vector>
#include <string>

class StartMatchCommand: public Command {
public:
	StartMatchCommand(GameInfo& info, int senderSocket);
	virtual ~StartMatchCommand();

	virtual void execute(std::vector<std::string> args);

private:
	GameInfo& info;
	int sender;
};

#endif /* STARTMATCHCOMMAND_H_ */
