/*
 * StartMatchCommand.h
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#ifndef STARTMATCHCOMMAND_H_
#define STARTMATCHCOMMAND_H_

#include "Command.h"
#include "GameSet.h"

#include <vector>
#include <string>

class StartMatchCommand: public Command {
public:
	StartMatchCommand(GameSet& info);
	virtual ~StartMatchCommand();

	virtual void execute(int sender, std::vector<std::string> args);

private:
	GameSet& info;
};

#endif /* STARTMATCHCOMMAND_H_ */
