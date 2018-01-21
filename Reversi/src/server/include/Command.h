/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex5
 **************************************/

#ifndef COMMAND_H_
#define COMMAND_H_

#include <vector>
#include <string>

#include "CommandResult.h"

class Command {
public:
	virtual ~Command();

	virtual CommandResult execute(int sender, std::vector<std::string> args) = 0;
};

#endif /* COMMAND_H_ */
