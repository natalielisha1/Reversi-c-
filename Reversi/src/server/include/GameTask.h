/*
 * GameTask.h
 *
 *  Created on: Jan 17, 2018
 *      Author: ofek286
 */

#ifndef GAMETASK_H_
#define GAMETASK_H_

#include "Task.h"
#include "CommandResult.h"

class GameTask: public Task {
public:
	GameTask(void *arg);
	virtual ~GameTask() {};
	virtual void execute();
};

#endif /* GAMETASK_H_ */
