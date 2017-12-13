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
#include <sys/socket.h>

#define SEND_FLAGS 0

class Command {
public:
	virtual ~Command();

	virtual void execute(std::vector<std::string> args) = 0;
};

#endif /* COMMAND_H_ */
