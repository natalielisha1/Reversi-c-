/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex5
 **************************************/

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
