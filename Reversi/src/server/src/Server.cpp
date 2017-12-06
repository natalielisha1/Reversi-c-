/*
 * Server.cpp
 *
 *  Created on: Dec 3, 2017
 *      Author: ofek286
 */

#include "Server.h"
using namespace std;

Server::Server(): serverSocket(0),
				  clientASock(0),
				  clientBSock(0),
				  clientALen(sizeof(struct sockaddr_in)),
				  clientBLen(sizeof(struct sockaddr_in)) {
	ifstream serverConfig("server_port.txt");
	if (!serverConfig.is_open()) {
		throw runtime_error("File not opening");
	}
	port = 0;
	serverConfig >> port;

	serverConfig.close();
}

Server::Server(int port): port(port), serverSocket(0),
						  clientASock(0), clientBSock(0),
						  clientALen(sizeof(struct sockaddr_in)),
						  clientBLen(sizeof(struct sockaddr_in)){
	//nothing right now

}

Server::~Server() {
	//nothing right now
}

void Server::start() {
	// Create a socket point
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1) {
		throw "Error opening socket";
	}
	// Assign a local address to the socket
	bzero((void *)&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(port);
	if (bind(serverSocket, (struct sockaddr *)&server, sizeof(server)) < 0) {
		throw "Error on binding";
	}
	// Start listening to incoming connections
	listen(serverSocket, MAX_CONNECTED_CLIENTS);
	// Define the client socket's structures
	bzero((void *)&clientA, sizeof(clientA));
	bzero((void *)&clientB, sizeof(clientB));
	while (true) {
		cout << "Waiting for client connections..." << endl;
		clientASock = accept(serverSocket, (struct sockaddr *)&clientA, (socklen_t*)&clientALen);
		if (clientASock == -1) {
			throw "Error on accept 1";
		}
		cout << "Client 1 connected" << endl;
		clientBSock = accept(serverSocket, (struct sockaddr *)&clientB, (socklen_t*)&clientBLen);
		if (clientBSock == -1) {
			throw "Error on accept B";
		}
		cout << "Client 2 connected" << endl;
		string order1 = "1";
		string order2 = "2";
		send(clientASock, order1.c_str(), order1.length(), SEND_FLAGS);
		send(clientBSock, order2.c_str(), order2.length(), SEND_FLAGS);

		bool ok = true;
		while (ok) {
			ok = handleClient(clientASock, '1', clientBSock);
			if (!ok) {
				continue;
			}
			ok = handleClient(clientBSock, '2', clientASock);
		}
		close(clientASock);
		close(clientBSock);
	}
}

void Server::stop() {
	close(serverSocket);
}

bool Server::handleClient(int clientA, char curr, int clientB) {
	char buffer[BUFFER_SIZE] = {0};
	string endConnection = "END";
	int readSize;
	int writeSize;
	while (true) {
		// Read new exercise arguments
		readSize = recv(clientA, buffer, BUFFER_SIZE, RECV_FLAGS);
		if (readSize == -1) {
			cout << "Error reading from client " << curr << endl;
			return false;
		} else if (readSize == 0) {
			cout << "Client " << curr << " disconnected" << endl;
			return false;
		} else if (strcmp(endConnection.c_str(), buffer) == 0){
			cout << "Game ended!" << endl;
			return false;
		} else {
			cout << buffer;
		}

		// Write the result back to the client
		writeSize = send(clientB, buffer, strlen(buffer), SEND_FLAGS);
		if (writeSize == -1) {
			cout << endl << "Error writing to client " << curr << endl;
			return false;
		}
		if (writeSize != BUFFER_SIZE) {
			cout << endl;
			return true;
		}
	}
	return true;
}
