/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex7
 **************************************/

#include "ThreadPool.h"

ThreadPool *ThreadPool::theInstance = NULL;
pthread_mutex_t ThreadPool::lock = PTHREAD_MUTEX_INITIALIZER;

void ThreadPool::initialize() {
	pthread_mutex_init(&lock, NULL);
}

ThreadPool *ThreadPool::getInstance(int threadNum) {
	if (theInstance == NULL) {
		pthread_mutex_lock(&lock);
		if (theInstance == NULL) {
			theInstance = new ThreadPool(threadNum);
		}
		pthread_mutex_unlock(&lock);
	}
	return theInstance;
}

ThreadPool *ThreadPool::getInstance() {
	if (theInstance == NULL) {
		pthread_mutex_lock(&lock);
		if (theInstance == NULL) {
			theInstance = new ThreadPool(DEFAULT_THREAD_NUM);
		}
		pthread_mutex_unlock(&lock);
	}
	return theInstance;
}

void ThreadPool::deleteInstance() {
	if (theInstance != NULL) {
		pthread_mutex_lock(&lock);
		if (theInstance != NULL) {
			delete theInstance;
			theInstance = NULL;
		}
		pthread_mutex_unlock(&lock);
	}
}

ThreadPool::ThreadPool(int threadNum): stopped(false),
									   threadNum(threadNum){
	pthread_mutex_init(&queueLock, NULL);
	threads = new pthread_t[threadNum];
	for (int i = 0; i < threadNum; i++) {
		pthread_create(&(threads[i]), NULL, execute, this);
	}
}

void ThreadPool::addTask(Task* task) {
	pthread_mutex_lock(&queueLock);
	tasks.push(task);
	pthread_mutex_unlock(&queueLock);
}

void ThreadPool::terminate() {
	stopped = true;
	GameSet *games = GameSet::getInstance();
	games->interruptMatches();
}

bool ThreadPool::getExit() const {
	return stopped;
}

ThreadPool::~ThreadPool() {
	for (int i = 0; i < threadNum; i++) {
		//pthread_kill(threads[i], SIGUSR1);
		pthread_join(threads[i], NULL);
	}
	delete[] threads;
}

void ThreadPool::executeTasks() {
	while (!stopped) {
		pthread_mutex_lock(&queueLock);
		if (!tasks.empty()) {
			Task *task = tasks.front();
			tasks.pop();
			pthread_mutex_unlock(&queueLock);
			task->execute();
			delete task;
		} else {
			pthread_mutex_unlock(&queueLock);
			sleep(1);
		}
	}
}

void* ThreadPool::execute(void* arg) {
	ThreadPool *pool = (ThreadPool *)arg;
	pool->executeTasks();
	return NULL;
}
