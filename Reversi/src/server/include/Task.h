/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex7
 **************************************/

#ifndef TASK_H_
#define TASK_H_

#include <sys/socket.h>
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <string.h>

#include "CommandResult.h"
#include "VerboseController.h"
#include "CommandsManager.h"
#include "ToolsForStrings.h"
#include "ExitController.h"

#define BUFFER_SIZE 2000

#define RECV_FLAGS 0

class Task {
public:
	Task(void *arg):arg(arg) {};
	virtual ~Task() {};
	virtual void execute() = 0;
	static CommandResult handleCommand(int client);
protected:
	void *arg;
};

#endif /* TASK_H_ */
