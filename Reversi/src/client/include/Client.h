/*
 * Client.h
 *
 *  Created on: Dec 3, 2017
 *      Author: ofek286
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <netinet/in.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <string>

#define BUFFER_SIZE 2000
#define RECV_FLAGS 0
#define SEND_FLAGS 0

class Client {
public:
	Client(const char *serverIP, int serverPort);
	~Client();

	void connectToServer();
	int sendMessage(const char *msg);
	void readMessage();
	void waitForCue();
	int getOrder();
private:
	const char *serverIP;
	int serverPort;
	int clientSocket;
	struct sockaddr_in serverAddress;
};

#endif /* CLIENT_H_ */
