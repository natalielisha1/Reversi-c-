/*
 * ListGamesCommand.h
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#ifndef LISTGAMESCOMMAND_H_
#define LISTGAMESCOMMAND_H_

#include "Command.h"
#include "GameInfo.h"

#include <vector>
#include <string>

class ListGamesCommand: public Command {
public:
	ListGamesCommand(GameInfo& info, int senderSocket);
	virtual ~ListGamesCommand();

	virtual void execute(std::vector<std::string> args);

private:
	GameInfo& info;
	int sender;
};

#endif /* LISTGAMESCOMMAND_H_ */
