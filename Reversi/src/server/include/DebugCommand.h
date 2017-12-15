/*
 * DebugCommand.h
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#ifndef DEBUGCOMMAND_H_
#define DEBUGCOMMAND_H_

#include "Command.h"
#include "GameSet.h"

#include <vector>
#include <string>

class DebugCommand: public Command {
public:
	DebugCommand(GameSet& info);
	virtual ~DebugCommand();

	virtual void execute(int sender, std::vector<std::string> args);

private:
	GameSet& info;
};

#endif /* DEBUGCOMMAND_H_ */
