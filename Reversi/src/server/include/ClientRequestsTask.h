/*
 * ClientRequestsTask.h
 *
 *  Created on: Jan 17, 2018
 *      Author: ofek286
 */

#ifndef CLIENTREQUESTSTASK_H_
#define CLIENTREQUESTSTASK_H_

#include "Task.h"
#include "GameTask.h"
#include "ThreadPool.h"
#include "GameSet.h"

class ClientRequestsTask: public Task {
public:
	ClientRequestsTask(void *arg);
	virtual ~ClientRequestsTask() {};
	virtual void execute();
};

#endif /* CLIENTREQUESTSTASK_H_ */
