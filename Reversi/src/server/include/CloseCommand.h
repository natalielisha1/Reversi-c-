/*
 * CloseCommand.h
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#ifndef CLOSECOMMAND_H_
#define CLOSECOMMAND_H_

#include "Command.h"
#include "GameInfo.h"

#include <vector>
#include <string>

class CloseCommand: public Command {
public:
	CloseCommand(GameInfo& info, int senderSocket);
	virtual ~CloseCommand();

	virtual void execute(std::vector<std::string> args);

private:
	GameInfo& info;
	int sender;
};

#endif /* CLOSECOMMAND_H_ */
