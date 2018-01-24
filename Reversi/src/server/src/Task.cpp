/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex7
 **************************************/

#include "Task.h"
using namespace std;

/***************************************
 * Function Name: handleCommand
 * The Input: socket id of a client
 * The Output: the command's result
 * The Function Operation: handling the client's
 * command and returning if the operation succeeded
 **************************************/
CommandResult Task::handleCommand(int client) {
	//Cout mutex & verbose status
	VerboseController *verbose = VerboseController::getInstance();
	CommandsManager *cmdManager = CommandsManager::getInstance();
	ExitController *exitController = ExitController::getInstance();

	//Creating a buffer
	char buffer[BUFFER_SIZE] = {0};
	//Keeping the message
	string msg = "";
	//Creating vars to keep the sockets' responses
	int readSize;
	while (true) {
		//Reading the message
		readSize = recv(client, buffer, BUFFER_SIZE, RECV_FLAGS);
		while (readSize == -1) {
			if (exitController->getExit() == true) {
				return CommandResult(false);
			}
			//Re-reading the message (timeout)
			readSize = recv(client, buffer, BUFFER_SIZE, RECV_FLAGS);
		}
		if (readSize <= 0) {
			//Client disconnected
			verbose->lockCout();
			cout << "Client " << client << " disconnected" << endl;
			verbose->unlockCout();
			return CommandResult(false);
		}

		msg.append(buffer);
		memset(buffer, 0, BUFFER_SIZE);

		if (readSize != BUFFER_SIZE) {
			break;
		}
	}
	if (verbose->getVerbose()) {
		verbose->lockCout();
		cout << client << ": " << msg << endl;
		verbose->unlockCout();
	}
	pair<string, vector<string> > cmd = extractCommand(msg);
	return cmdManager->executeCommand(client, cmd.first, cmd.second);
}

