/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex4
 **************************************/

#include "Server.h"
using namespace std;

/***************************************
 * Function Name: Server (Constructor)
 * The Input: nothing
 * The Output: the server instance
 * The Function Operation: initializing
 *  the server from config file
 **************************************/
Server::Server(): serverSocket(0),
				  clientASock(0),
				  clientBSock(0),
				  clientALen(sizeof(struct sockaddr_in)),
				  clientBLen(sizeof(struct sockaddr_in)),
				  cmdManager(games),
				  verbose(false){
	//Reading the config file and applying the config
	ifstream serverConfig("server_port.txt");
	if (!serverConfig.is_open()) {
		throw runtime_error("File not opening");
	}
	port = 0;
	serverConfig >> port;
	//Closing the file
	serverConfig.close();
}

/***************************************
 * Function Name: Server (Constructor)
 * The Input: verbose flag
 * The Output: the server instance
 * The Function Operation: initializing
 *  the server from config file
 **************************************/
Server::Server(bool verbose): serverSocket(0),
				  	  	  	  clientASock(0),
							  clientBSock(0),
							  clientALen(sizeof(struct sockaddr_in)),
							  clientBLen(sizeof(struct sockaddr_in)),
							  cmdManager(games),
							  verbose(verbose){
	//Reading the config file and applying the config
	ifstream serverConfig("server_port.txt");
	if (!serverConfig.is_open()) {
		throw runtime_error("File not opening");
	}
	port = 0;
	serverConfig >> port;
	//Closing the file
	serverConfig.close();
}

/***************************************
 * Function Name: Server (Constructor)
 * The Input: the port
 * The Output: the server instance
 * The Function Operation: initializing
 *  the server from port input
 **************************************/
Server::Server(int port): port(port), serverSocket(0),
						  clientASock(0), clientBSock(0),
						  clientALen(sizeof(struct sockaddr_in)),
						  clientBLen(sizeof(struct sockaddr_in)),
						  cmdManager(games),
						  verbose(false){
	//Nothing right now

}

/***************************************
 * Function Name: Server (Constructor)
 * The Input: the port and verbose flag
 * The Output: the server instance
 * The Function Operation: initializing
 *  the server from port input
 **************************************/
Server::Server(int port, bool verbose): port(port), serverSocket(0),
						  	  	  	  	clientASock(0), clientBSock(0),
										clientALen(sizeof(struct sockaddr_in)),
										clientBLen(sizeof(struct sockaddr_in)),
										cmdManager(games),
										verbose(verbose){
	//Nothing right now

}

/***************************************
 * Function Name: ~Server (Destructor)
 * The Input: no input
 * The Output: no output
 * The Function Operation: nothing
 **************************************/
Server::~Server() {
	//Nothing right now
}


/***************************************
 * Function Name: start
 * The Input: no input
 * The Output: no output
 * The Function Operation: starting the
 *  server
 **************************************/
void Server::start() {
	//Creating a socket pointer
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1) {
		//The socket wasn't created, so we crash
		throw "Error opening socket";
	}
	//Assigning a local address to the socket
	bzero((void *)&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(port);
	//Binding the port
	if (bind(serverSocket, (struct sockaddr *)&server, sizeof(server)) < 0) {
		//The binding failed, so we crash
		throw "Error on binding";
	}
	//Starting listening to incoming connections
	listen(serverSocket, MAX_CONNECTED_CLIENTS);

	while (true) {
		//Cleaning the clients' info structures
		bzero((void *)&clientA, sizeof(clientA));
		bzero((void *)&clientB, sizeof(clientB));
		//Waiting for the clients to connect
		cout << "Waiting for client connections..." << endl;
		//Connecting the first client
		clientASock = accept(serverSocket, (struct sockaddr *)&clientA, (socklen_t*)&clientALen);
		if (clientASock == -1) {
			//The first client's connection failed, so we crash
			throw "Error on accept 1";
		}
		//The first client connected
		cout << "Client 1 connected" << endl;
		//Connecting the second client
		clientBSock = accept(serverSocket, (struct sockaddr *)&clientB, (socklen_t*)&clientBLen);
		if (clientBSock == -1) {
			//The second client's connection failed, so we crash
			close(clientASock);
			throw "Error on accept B";
		}
		//The second client connected
		cout << "Client 2 connected" << endl;
		//Sending the clients their orders
		string order1 = "1";
		string order2 = "2";
		send(clientASock, order1.c_str(), order1.length(), SEND_FLAGS);
		send(clientBSock, order2.c_str(), order2.length(), SEND_FLAGS);

		/*
		//Handling the requests
		bool ok = true;
		while (ok) {
			ok = handleClient(clientASock, '1', clientBSock);
			if (!ok) {
				continue;
			}
			ok = handleClient(clientBSock, '2', clientASock);
		}
		*/

		//Handling the requests
		bool ok = true;
		while (ok) {
			ok = handleCommand(clientASock);
			if (!ok) {
				continue;
			}
			ok = handleCommand(clientBSock);
		}

		//One or both of the clients disconnected, so we start-over
		close(clientASock);
		close(clientBSock);
	}
}

/***************************************
 * Function Name: stop
 * The Input: no input
 * The Output: no output
 * The Function Operation: closing the
 *  socket
 **************************************/
void Server::stop() {
	close(serverSocket);
}

/***************************************
 * Function Name: handleClient
 * The Input: clients' sockets, and the
 *  current client
 * The Output: true - the handling
 *  succeeded (and the game is still
 *  running)
 *             false - otherwise
 * The Function Operation: getting message
 *  from clientA, checking it, and sending
 *  it to clientB (if required)
 **************************************/
bool Server::handleClient(int sender, char curr, int reciever) {
	//Creating string to check for game ending
	string endConnection = "END";
	//Creating a buffer
	char buffer[BUFFER_SIZE] = {0};
	//Creating vars to keep the sockets' responses
	int readSize;
	int writeSize;
	while (true) {
		//Reading the message
		readSize = recv(sender, buffer, BUFFER_SIZE, RECV_FLAGS);
		if (readSize == -1) {
			//Error in receiving
			cout << "Error reading from client " << curr << endl;
			return false;
		} else if (readSize == 0) {
			//Client disconnection
			cout << "Client " << curr << " disconnected" << endl;
			return false;
		} else if (strcmp(endConnection.c_str(), buffer) == 0) {
			//Game ending
			cout << "Game ended!" << endl;
			return false;
		} else if (verbose) {
			cout << buffer;
		}

		//Writing the message to the other client
		writeSize = send(reciever, buffer, strlen(buffer), SEND_FLAGS);
		if (writeSize == -1) {
			//Error in writing
			cout << endl << "Error writing to client " << curr << endl;
			return false;
		}
		if (writeSize != BUFFER_SIZE) {
			//The message received completely
			if (verbose) {
				cout << endl;
			}
			return true;
		}
	}
	return true;
}

bool Server::handleCommand(int client) {
	//Creating a buffer
	char buffer[BUFFER_SIZE] = {0};
	//Keeping the message
	string msg = "";
	//Creating vars to keep the sockets' responses
	int readSize;
	while (true) {
		//Reading the message
		readSize = recv(client, buffer, BUFFER_SIZE, RECV_FLAGS);
		if (readSize == -1) {
			//Error in receiving
			cout << "Error reading from client " << client << endl;
			return false;
		} else if (readSize == 0) {
			//Client disconnection
			cout << "Client " << client << " disconnected" << endl;
			return false;
		}

		msg.append(buffer);

		if (readSize != BUFFER_SIZE) {
			break;
		}
	}
	if (verbose) {
		cout << msg << endl;
	}
	pair<string, vector<string> > cmd = extractCommand(msg);
	cmdManager.executeCommand(client, cmd.first, cmd.second);
	return true;
}

bool Server::sendMessageToClient(int client, string& msg) {
	int writeSize;
	writeSize = send(client, msg.c_str(), msg.length(), SEND_FLAGS);
	if (writeSize == -1) {
		//Error in writing
		cout << "Error writing to client" << endl;
		return false;
	}
	return true;
}


//Outsider Functions
pair<string, vector<string> > extractCommand(string& msg) {
	string command;
	vector<string> args;
	string currentWord = "";
	bool foundCommand = false;

	if (msg.find(" ") == string::npos) {
		return make_pair(msg, args);
	}

	size_t index = 0;
	while ((index = msg.find(" ") != string::npos)) {
		currentWord = msg.substr(0, index);
		if (!foundCommand) {
			command = currentWord;
			foundCommand = true;
		} else {
			args.push_back(currentWord);
		}
	}

	return make_pair(command, args);
}
