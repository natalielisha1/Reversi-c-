/*
 * JoinCommand.h
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#ifndef JOINCOMMAND_H_
#define JOINCOMMAND_H_

#include "Command.h"
#include "GameInfo.h"

#include <vector>
#include <string>

class JoinCommand: public Command {
public:
	JoinCommand(GameInfo& info, int senderSocket);
	virtual ~JoinCommand();

	virtual void execute(std::vector<std::string> args);

private:
	GameInfo& info;
	int sender;
};

#endif /* JOINCOMMAND_H_ */
