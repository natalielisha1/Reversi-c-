/*
 * ListGamesCommand.h
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#ifndef LISTGAMESCOMMAND_H_
#define LISTGAMESCOMMAND_H_

#include "Command.h"
#include "GameSet.h"

#include <vector>
#include <string>

class ListGamesCommand: public Command {
public:
	ListGamesCommand(GameSet& info);
	virtual ~ListGamesCommand();

	virtual void execute(int sender, std::vector<std::string> args);

private:
	GameSet& info;
};

#endif /* LISTGAMESCOMMAND_H_ */
