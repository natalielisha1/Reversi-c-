/*
 * Server.h
 *
 *  Created on: Dec 3, 2017
 *      Author: ofek286
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

#define MAX_CONNECTED_CLIENTS 10
#define BUFFER_SIZE 2000
#define RECV_FLAGS 0
#define SEND_FLAGS 0

class Server {
public:
	Server(int port);
	Server();
	~Server();

	void start();
	void stop();
private:
	int port;
	int serverSocket;
	struct sockaddr_in server;

	int clientASock;
	int clientBSock;
	struct sockaddr_in clientA;
	struct sockaddr_in clientB;
	socklen_t clientALen;
	socklen_t clientBLen;

	bool handleClient(int clientA, char curr, int clientB);
};

#endif /* SERVER_H_ */
