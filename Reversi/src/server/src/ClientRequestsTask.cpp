/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex7
 **************************************/

#include "ClientRequestsTask.h"
#include "Server.h"

/***************************************
 * Function Name: clientCommunicationThreadMain
 * The Input: a pointer of an argument
 * The Output: NULL
 * The Function Operation: the main function
 * of the client's communication thread
 **************************************/
void *clientCommunicationThreadMain(void *arg) {
	//Getting the client's file descriptor
	long socketAsLong = (long) arg;
	int currClientSocket = (int) socketAsLong;

	//Var to hold the command result
	CommandResult result;

	//Getting the thread pool to send the new task
	ThreadPool *threadPool = ThreadPool::getInstance();

	//Getting the game set to send the new game
	GameSet *games = GameSet::getInstance();

	//Handling the requests
	bool ok = true;
	while (ok) {
		result = Task::handleCommand(currClientSocket);
		ok = result.getStatus();
		if (!ok || (result.getCommand() == CommandResult::Start &&
					result.getResult() == NO_ERROR_RESULT)) {
			ok = false;
		} else if (result.getCommand() == CommandResult::Join &&
				   result.getResult() == NO_ERROR_RESULT) {
			GameInfo *currGame = games->getGameInfo(currClientSocket);
			threadPool->addTask(new GameTask((void *) currGame));
			ok = false;
		}
	}

	return NULL;
}

/***************************************
 * Function Name: ClientRequestsTask
 * The Input: a pointer of an argument
 * The Output: a ClientRequestsTask instance
 * The Function Operation: initializing the
 * task with the given arguments
 **************************************/
ClientRequestsTask::ClientRequestsTask(void *arg): Task(arg) {
	//Nothing right now
}

/***************************************
 * Function Name: execute
 * The Input: no input
 * The Output: no output
 * The Function Operation: executing the
 * clientCommunicationThreadMain function
 * using the ClientRequestsTask intance's
 * arguments
 **************************************/
void ClientRequestsTask::execute() {
	clientCommunicationThreadMain(arg);
}
