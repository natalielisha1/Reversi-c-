/*
 * Client.cpp
 *
 *  Created on: Dec 3, 2017
 *      Author: ofek286
 */

#include "Client.h"
using namespace std;

Client::Client(): clientSocket(0) {
	ifstream serverConfig("server_address.txt");
	//string tempServerIP;
	serverConfig >> serverIP;
	//serverIP = tempServerIP.c_str();
	serverPort = 0;
	serverConfig >> serverPort;

	serverConfig.close();
}

Client::Client(string &serverIP, int serverPort): serverIP(serverIP), serverPort(serverPort), clientSocket(0) {
	//nothing right now

}

Client::~Client() {
	//nothing right now
}

void Client::connectToServer() {
	// Create a socket point
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket < 0) {
		throw runtime_error("Error opening socket");
	}
	// Create a clean structure for the server address
	bzero((char *)&serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr(serverIP.c_str());
	serverAddress.sin_port = htons(serverPort);
	// Establish a connection with the server
	if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
		throw runtime_error("Error connecting to server");
	}
	cout << "Connected to server" << endl;
}

void Client::disconnect() {
	close(clientSocket);
}

int Client::sendMessage(const char *msg) {
	return send(clientSocket, msg, strlen(msg), SEND_FLAGS);
}

string Client::readMessage() {
	string toReturn = string("");
	char buffer[BUFFER_SIZE] = {0};
	int readSize;
	while (true) {
		if ((readSize = recv(clientSocket, buffer, BUFFER_SIZE, RECV_FLAGS)) > 0) {
			//cout << buffer;
			toReturn.append(buffer);
		}
		if (readSize != BUFFER_SIZE) {
			//cout << endl;
			return toReturn;
		}
	}
	//cout << endl;
}

void Client::waitForCue() {
	string cueX = string("X: It's your move");
	string cueO = string("O: It's your move");
	char buffer[BUFFER_SIZE] = {0};
	int readSize;
	while (true) {
		if ((readSize = recv(clientSocket, buffer, BUFFER_SIZE, RECV_FLAGS)) > 0) {
			if (strcmp(cueX.c_str(), buffer) == 0) {
				return;
			} else if (strcmp(cueO.c_str(), buffer) == 0) {
				return;
			}
		}
	}
}

int Client::getOrder() {
	char buffer[BUFFER_SIZE] = {0};
	string first = string("1");
	string second = string("2");
	int readSize;
	while (true) {
		if ((readSize = recv(clientSocket, buffer, BUFFER_SIZE, RECV_FLAGS)) > 0) {
			if (strcmp(first.c_str(), buffer) == 0) {
				return 1;
			} else if (strcmp(second.c_str(), buffer) == 0) {
				return 2;
			}
		}
	}
	return -1;
}
