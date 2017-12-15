/*
 * Command.h
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include <vector>
#include <string>

class Command {
public:
	virtual ~Command();

	virtual void execute(int sender, std::vector<std::string> args) = 0;
};

#endif /* COMMAND_H_ */
