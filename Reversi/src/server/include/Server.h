/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex4
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

#define MAX_GAMES 5

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
private:
	bool verbose;
	pthread_mutex_t verboseMutex;

	int port;
	int serverSocket;
	struct sockaddr_in server;

	//int clientASock;
	//int clientBSock;
	//struct sockaddr_in clientA;
	//struct sockaddr_in clientB;
	//socklen_t clientALen;
	//socklen_t clientBLen;

	GameSet games;
	pthread_mutex_t gamesMutex;

	CommandsManager cmdManager;

	std::vector<pthread_t *> gameThreads;

	GameInfo *lastUsedGame;

	void addThread(int client);

	bool handleClient(int sender, char curr, int reciever);
	bool handleCommand(int client);

	bool getVerbose();
};

//Outsider Functions
std::pair<std::string, std::vector<std::string> > extractCommand(std::string& msg);
void *gameThreadMain(void *arg);

#endif /* SERVER_H_ */
