/*
 * Server.cpp
 *
 *  Created on: Dec 3, 2017
 *      Author: ofek286
 */

#include "Server.h"

Server::Server(int port): port(port), serverSocket(0),
						  clientASock(0), clientBSock(0),
						  clientALen(sizeof(struct sockaddr_in)),
						  clientBLen(sizeof(struct sockaddr_in)){
	//TODO: WRITE

}

Server::~Server() {
	// Nothing right now
}

void Server::start() {
	//TODO: WRITE
}

void Server::stop() {
	//TODO: WRITE
}

bool Server::handleClient(int clientA, char curr, int clientB) {
	//TODO: WRITE

	return false;
}
