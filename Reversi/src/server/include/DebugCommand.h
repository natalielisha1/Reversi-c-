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
	DebugCommand(GameSet& info);
	virtual ~DebugCommand();

	virtual void execute(int sender, std::vector<std::string> args);

private:
	GameSet& info;
};

#endif /* DEBUGCOMMAND_H_ */
