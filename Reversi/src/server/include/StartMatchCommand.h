/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex5
 **************************************/

#ifndef STARTMATCHCOMMAND_H_
#define STARTMATCHCOMMAND_H_

#include "Command.h"
#include "GameSet.h"

#include <vector>
#include <string>

class StartMatchCommand: public Command {
public:
	StartMatchCommand();
	virtual ~StartMatchCommand();

	virtual CommandResult execute(int sender, std::vector<std::string> args);

private:
	GameSet *games;
};

#endif /* STARTMATCHCOMMAND_H_ */
