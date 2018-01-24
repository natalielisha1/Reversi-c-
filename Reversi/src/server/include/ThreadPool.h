/*
 * ThreadPool.h
 *
 *  Created on: Jan 17, 2018
 *      Author: ofek286
 */

#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include <queue>
#include <pthread.h>
#include <signal.h>

#include "Task.h"
#include "GameSet.h"

#define DEFAULT_THREAD_NUM 10

class ThreadPool {
public:
	static void initialize();

	static ThreadPool *getInstance(int threadNum);
	static ThreadPool *getInstance();

	static void deleteInstance();

	void addTask(Task *task);
	void terminate();

	bool getExit() const;
private:
	static ThreadPool *theInstance;
	static pthread_mutex_t lock;

	ThreadPool(int threadNum);
	~ThreadPool();

	std::queue<Task *> tasks;
	pthread_t* threads;

	bool stopped;

	int threadNum;

	pthread_mutex_t queueLock;

	void executeTasks();

	static void *execute(void *arg);
};

#endif /* THREADPOOL_H_ */
