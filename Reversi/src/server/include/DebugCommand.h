/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex5
 **************************************/

#ifndef DEBUGCOMMAND_H_
#define DEBUGCOMMAND_H_

#include "Command.h"
#include "GameSet.h"

#include <vector>
#include <string>

class DebugCommand: public Command {
public:
	DebugCommand();
	virtual ~DebugCommand();

	virtual CommandResult execute(int sender, std::vector<std::string> args);

private:
	GameSet *games;
};

#endif /* DEBUGCOMMAND_H_ */
