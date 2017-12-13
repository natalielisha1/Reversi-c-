/*
 * DebugCommand.h
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#ifndef DEBUGCOMMAND_H_
#define DEBUGCOMMAND_H_

#include "Command.h"
#include "GameInfo.h"

#include <vector>
#include <string>

class DebugCommand: public Command {
public:
	DebugCommand(GameInfo& info, int senderSocket);
	virtual ~DebugCommand();

	virtual void execute(std::vector<std::string> args);

private:
	GameInfo& info;
	int sender;
};

#endif /* DEBUGCOMMAND_H_ */
