/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex5
 **************************************/

#ifndef CLOSECOMMAND_H_
#define CLOSECOMMAND_H_

#include "Command.h"
#include "GameSet.h"

#include <vector>
#include <string>

class CloseCommand: public Command {
public:
	CloseCommand();
	virtual ~CloseCommand();

	virtual CommandResult execute(int sender, std::vector<std::string> args);

private:
	GameSet *games;
};

#endif /* CLOSECOMMAND_H_ */
