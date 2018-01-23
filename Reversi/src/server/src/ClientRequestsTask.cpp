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
	//Server *theServer = (Server *) arg;
	long socketAsLong = (long) arg;
	int currClientSocket = (int) socketAsLong;
	CommandResult result;
	ThreadPool *threadPool = ThreadPool::getInstance();
	GameSet *games = GameSet::getInstance();

	//Handling the requests
	bool ok = true;
	while (ok) {
//		if (theServer->getExit()) {
//			close(currClientSocket);
//			return NULL;
//		}
		result = Task::handleCommand(currClientSocket);
		ok = result.getStatus();
		if (!ok || (result.getCommand() == CommandResult::Start &&
					result.getResult() == NO_ERROR_RESULT)) {
			ok = false;
		} else if (result.getCommand() == CommandResult::Join &&
				   result.getResult() == NO_ERROR_RESULT) {
			GameInfo *currGame = games->getGameInfo(currClientSocket);
			threadPool->addTask(new GameTask((void *) currGame));
//			theServer->addThread(currClientSocket);
			ok = false;
		}
//		} else if (theServer->getExit()) {
//			ok = false;
//			close(currClientSocket);
//		}
	}

	return NULL;
}

ClientRequestsTask::ClientRequestsTask(void *arg): Task(arg) {
	//Nothing right now
}

void ClientRequestsTask::execute() {
	clientCommunicationThreadMain(arg);
}
