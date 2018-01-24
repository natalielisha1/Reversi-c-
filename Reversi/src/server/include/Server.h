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
#define MAX_THREADS 10

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
//	pthread_mutex_t verboseMutex;

	int port;
	int serverSocket;
	struct sockaddr_in server;

	//GameSet games;
	//pthread_mutex_t gamesMutex;

	CommandsManager *cmdManager;

	ThreadPool *threadPool;

//	std::vector<pthread_t *> gameThreads;
//	std::vector<pthread_t *> clientCommunicationThreads;

//	GameInfo *lastUsedGame;
//	pthread_mutex_t lastGameMutex;

//	int lastUsedClient;
//	pthread_mutex_t lastClientMutex;

	std::vector<int> connectedClients;

	VerboseController *verbose;

	ExitController *exitController;

	//bool serverExit;
	//pthread_mutex_t serverExitMutex;

	void addThread(int client);

	bool getVerbose();

	bool handleCommand(int client);

	bool getExit();
	void setExit();
};

//Outsider Functions
std::pair<std::string, std::vector<std::string> > extractCommand(std::string& msg);

#endif /* SERVER_H_ */
