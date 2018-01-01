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

#include "CommandsManager.h"
#include "GameInfo.h"
#include "Tools.h"

#define MAX_CONNECTED_CLIENTS 10

#define BUFFER_SIZE 2000

#define RECV_FLAGS 0
#define SEND_FLAGS 0

#define SOCKET_TIMEOUT 15

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
	bool verbose;
	pthread_mutex_t verboseMutex;

	int port;
	int serverSocket;
	struct sockaddr_in server;

	GameSet games;
	pthread_mutex_t gamesMutex;

	CommandsManager cmdManager;

	std::vector<pthread_t *> gameThreads;
	std::vector<pthread_t *> clientCommunicationThreads;

	GameInfo *lastUsedGame;
	pthread_mutex_t lastGameMutex;

	int lastUsedClient;
	pthread_mutex_t lastClientMutex;

	pthread_mutex_t coutMutex;

	bool serverExit;
	pthread_mutex_t serverExitMutex;

	void addThread(int client);

	bool handleCommand(int client);

	bool getVerbose();

	bool getExit();
	void setExit(bool exit);
};

//Outsider Functions
std::pair<std::string, std::vector<std::string> > extractCommand(std::string& msg);

#endif /* SERVER_H_ */
