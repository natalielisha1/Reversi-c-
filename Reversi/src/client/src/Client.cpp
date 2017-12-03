/*
 * Client.cpp
 *
 *  Created on: Dec 3, 2017
 *      Author: ofek286
 */

#include "Client.h"

Client::Client(const char *serverIP, int serverPort): serverIP(serverIP), serverPort(serverPort), clientSocket(0) {
	//TODO: WRITE

}

Client::~Client() {
	//nothing right now
}

void Client::connectToServer() {
	//TODO: WRITE
}

int Client::sendMessage(const char *msg) {
	//TODO: WRITE

	return -1;
}

void Client::readMessage() {
	//TODO: WRITE
}

void Client::waitForCue() {
	//TODO: WRITE
}

int Client::getOrder() {
	//TODO: WRITE

	return -1;
}
