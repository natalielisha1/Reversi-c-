/*
 * JoinCommand.h
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#ifndef JOINCOMMAND_H_
#define JOINCOMMAND_H_

#include "Command.h"
#include "GameSet.h"

#include <vector>
#include <string>

class JoinCommand: public Command {
public:
	JoinCommand(GameSet& info);
	virtual ~JoinCommand();

	virtual void execute(int sender, std::vector<std::string> args);

private:
	GameSet& info;
};

#endif /* JOINCOMMAND_H_ */
