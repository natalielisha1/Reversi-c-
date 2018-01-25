/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex7
 **************************************/

#include "ThreadPool.h"

ThreadPool *ThreadPool::theInstance = NULL;
pthread_mutex_t ThreadPool::lock = PTHREAD_MUTEX_INITIALIZER;

/***************************************
 * Function Name: initialize
 * The Input: no input
 * The Output: NULL
 * The Function Operation: initializing the
 * threadPool
 **************************************/
void ThreadPool::initialize() {
	pthread_mutex_init(&lock, NULL);
}

/***************************************
 * Function Name: getInstance
 * The Input: threadNum - number of the threads in
 * the thread pool
 * The Output: a pointer to a ThreadPool instance
 * The Function Operation: returning a ThreadPool
 * instance that contains the given amount of threads
 **************************************/
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

/***************************************
 * Function Name: getInstance
 * The Input: no input
 * the thread pool
 * The Output: a pointer to a ThreadPool instance
 * The Function Operation: returning a ThreadPool
 * instance
 **************************************/
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

/***************************************
 * Function Name: getInstance
 * The Input: no input
 * The Output: NULL
 * The Function Operation: deleting the ThreadPool
 * instance if exists
 **************************************/
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

/***************************************
 * Function Name: ThreadPool
 * The Input: threadNum - number of the threads in
 * the thread pool
 * The Output: a ThreadPool instance
 * The Function Operation: constructor of ThreadPool
 * instances
 **************************************/
ThreadPool::ThreadPool(int threadNum): stopped(false),
									   threadNum(threadNum){
	pthread_mutex_init(&queueLock, NULL);
	threads = new pthread_t[threadNum];
	for (int i = 0; i < threadNum; i++) {
		pthread_create(&(threads[i]), NULL, execute, this);
	}
}

/***************************************
 * Function Name: addTask
 * The Input: task - a pointer to a task instance
 * The Output: NULL
 * The Function Operation: adding a task to the thread pool
 **************************************/
void ThreadPool::addTask(Task* task) {
	pthread_mutex_lock(&queueLock);
	tasks.push(task);
	pthread_mutex_unlock(&queueLock);
}

/***************************************
 * Function Name: terminate
 * The Input: no input
 * The Output: NULL
 * The Function Operation: terminates the thread pool
 **************************************/
void ThreadPool::terminate() {
	stopped = true;
	GameSet *games = GameSet::getInstance();
	games->interruptMatches();
}

/***************************************
 * Function Name: getExit
 * The Input: no input
 * The Output: boolean value, true/false
 * The Function Operation: returning true if
 * should exit, otherwise false.
 **************************************/
bool ThreadPool::getExit() const {
	return stopped;
}

/***************************************
 * Function Name: ~ThreadPool
 * The Input: no input
 * The Output: no output
 * The Function Operation: destructor for ThreadPool
 * instances
 **************************************/
ThreadPool::~ThreadPool() {
	for (int i = 0; i < threadNum; i++) {
		//pthread_kill(threads[i], SIGUSR1);
		pthread_join(threads[i], NULL);
	}
	delete[] threads;
}

/***************************************
 * Function Name: executeTasks
 * The Input: no input
 * The Output: NULL
 * The Function Operation: executing the tasks
 * that the thread pool contains
 **************************************/
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

/***************************************
 * Function Name: execute
 * The Input: a pointer to an argument
 * The Output: NULL
 * The Function Operation: executes the executeTasks
 * function
 **************************************/
void* ThreadPool::execute(void* arg) {
	ThreadPool *pool = (ThreadPool *)arg;
	pool->executeTasks();
	return NULL;
}
