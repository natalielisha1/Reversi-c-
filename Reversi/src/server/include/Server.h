/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex5
 **************************************/

#ifndef SERVER_H_
#define SERVER_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <map>
#include <utility>

#include "VerboseController.h"
#include "CommandsManager.h"
#include "GameInfo.h"
#include "Tools.h"
#include "ThreadPool.h"
#include "ClientRequestsTask.h"

#define MAX_CONNECTED_CLIENTS 10
#define MAX_THREADS 5

#define SEND_FLAGS 0

#define SOCKET_TIMEOUT 5

class Server {
public:
	Server();
	Server(bool verbose);
	Server(int port);
	Server(int port, bool verbose);
	~Server();

	void start();
	void stop();

	bool sendMessageToClient(int client, std::string& msg);

	friend void *gameThreadMain(void *arg);
	friend void *clientCommunicationThreadMain(void *arg);
	friend void *exitThreadMain(void *arg);
private:
	int port;
	int serverSocket;
	struct sockaddr_in server;

	CommandsManager *cmdManager;

	ThreadPool *threadPool;

	std::vector<int> connectedClients;

	VerboseController *verbose;

	ExitController *exitController;

	void addThread(int client);

	bool getVerbose();

	bool handleCommand(int client);

	bool getExit();
	void setExit();
};

//Outsider Functions
std::pair<std::string, std::vector<std::string> > extractCommand(std::string& msg);

#endif /* SERVER_H_ */
