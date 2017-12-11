/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex4
 **************************************/

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
#include <fstream>
#include <stdexcept>

#define BUFFER_SIZE 2000
#define RECV_FLAGS 0
#define SEND_FLAGS 0

class Client {
public:
	Client(std::string &serverIP, int serverPort);
	Client();
	~Client();

	void connectToServer();
	void disconnect();

	int sendMessage(const char *msg);
	std::string readMessage();

	void waitForCue();
	int getOrder();
private:
	std::string serverIP;
	int serverPort;
	int clientSocket;
	struct sockaddr_in serverAddress;
};

#endif /* CLIENT_H_ */
