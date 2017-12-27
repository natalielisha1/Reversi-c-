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
				  cmdManager(games),
				  lastUsedGame(NULL),
				  lastUsedClient(-1),
				  serverExit(false),
				  verbose(false) {
	//Reading the config file and applying the config
	ifstream serverConfig("server_port.txt");
	if (!serverConfig.is_open()) {
		throw runtime_error("File not opening");
	}
	port = 0;
	serverConfig >> port;
	//Closing the file
	serverConfig.close();
	pthread_mutex_init(&gamesMutex, NULL);
	pthread_mutex_init(&verboseMutex, NULL);
	pthread_mutex_init(&lastGameMutex, NULL);
	pthread_mutex_init(&lastClientMutex, NULL);
	pthread_mutex_init(&coutMutex, NULL);
}

/***************************************
 * Function Name: Server (Constructor)
 * The Input: verbose flag
 * The Output: the server instance
 * The Function Operation: initializing
 *  the server from config file
 **************************************/
Server::Server(bool verbose): serverSocket(0),
							  cmdManager(games),
							  lastUsedGame(NULL),
							  lastUsedClient(-1),
							  serverExit(false),
							  verbose(verbose) {
	//Reading the config file and applying the config
	ifstream serverConfig("server_port.txt");
	if (!serverConfig.is_open()) {
		throw runtime_error("File not opening");
	}
	port = 0;
	serverConfig >> port;
	//Closing the file
	serverConfig.close();
	pthread_mutex_init(&gamesMutex, NULL);
	pthread_mutex_init(&verboseMutex, NULL);
	pthread_mutex_init(&lastGameMutex, NULL);
	pthread_mutex_init(&lastClientMutex, NULL);
	pthread_mutex_init(&coutMutex, NULL);
}

/***************************************
 * Function Name: Server (Constructor)
 * The Input: the port
 * The Output: the server instance
 * The Function Operation: initializing
 *  the server from port input
 **************************************/
Server::Server(int port): port(port), serverSocket(0),
						  cmdManager(games),
						  lastUsedGame(NULL),
						  lastUsedClient(-1),
						  serverExit(false),
						  verbose(false){
	pthread_mutex_init(&gamesMutex, NULL);
	pthread_mutex_init(&verboseMutex, NULL);
	pthread_mutex_init(&lastGameMutex, NULL);
	pthread_mutex_init(&lastClientMutex, NULL);
	pthread_mutex_init(&coutMutex, NULL);
}

/***************************************
 * Function Name: Server (Constructor)
 * The Input: the port and verbose flag
 * The Output: the server instance
 * The Function Operation: initializing
 *  the server from port input
 **************************************/
Server::Server(int port, bool verbose): port(port), serverSocket(0),
										cmdManager(games),
										lastUsedGame(NULL),
										lastUsedClient(-1),
										serverExit(false),
										verbose(verbose){
	pthread_mutex_init(&gamesMutex, NULL);
	pthread_mutex_init(&verboseMutex, NULL);
	pthread_mutex_init(&lastGameMutex, NULL);
	pthread_mutex_init(&lastClientMutex, NULL);
	pthread_mutex_init(&coutMutex, NULL);
}

/***************************************
 * Function Name: ~Server (Destructor)
 * The Input: no input
 * The Output: no output
 * The Function Operation: nothing
 **************************************/
Server::~Server() {
	for (vector<pthread_t *>::iterator it = gameThreads.begin(); it != gameThreads.end(); ++it) {
		delete (*it);
	}

	for (vector<pthread_t *>::iterator it = clientCommunicationThreads.begin(); it != clientCommunicationThreads.end(); ++it) {
		delete (*it);
	}
}


/***************************************
 * Function Name: start
 * The Input: no input
 * The Output: no output
 * The Function Operation: starting the
 *  server
 **************************************/
void Server::start() {
	pthread_t exitThread;

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
	//Setting a timeout - to be able to shutdown gracefully (almost) anytime
	struct timeval tv;
	tv.tv_sec = SOCKET_TIMEOUT;
	tv.tv_usec = 0;

	if (setsockopt(serverSocket, SOL_SOCKET, SO_RCVTIMEO, (struct timeval *)&tv, sizeof(struct timeval)) < 0) {
		//Timeout setting failed, so we crash
		throw "Error on setting timeout";
	}

	//Starting listening to incoming connections
	listen(serverSocket, MAX_CONNECTED_CLIENTS);

	int exitThreadResult = pthread_create(&exitThread, NULL, exitThreadMain, (void *) this);
	if (exitThreadResult) {
		cout << "Exit thread creation failed, exiting" << endl;
		return;
	} else {
		cout << "Enter 'exit' to close the server" << endl;
	}

	//Waiting for the clients to connect
	pthread_mutex_lock(&coutMutex);
	cout << "Waiting for client connections..." << endl;
	pthread_mutex_unlock(&coutMutex);

	while (true) {
		if (getExit()) {
			break;
		}
		int currClientSocket;
		struct sockaddr_in currClient;
		socklen_t clientLen = sizeof(struct sockaddr_in);
		//Cleaning the client's info structure
		bzero((void *)&currClient, sizeof(currClient));

		//Connecting the current client
		currClientSocket = accept(serverSocket, (struct sockaddr *)&currClient, (socklen_t*)&clientLen);

		bool exitNow = false;
		while (currClientSocket < 0 && !exitNow) {
			//Timeout (or failure), so we check for exit and get beck to accepting
			if (getExit()) {
				exitNow = true;
				break;
			}
			if (getVerbose()) {
				pthread_mutex_lock(&coutMutex);
				cout << "Client accept timeout, retrying.." << endl;
				pthread_mutex_unlock(&coutMutex);
			}
			//Cleaning and retrying the accept
			bzero((void *)&currClient, sizeof(currClient));
			currClientSocket = accept(serverSocket, (struct sockaddr *)&currClient, (socklen_t*)&clientLen);
		}
		if (exitNow) {
			break;
		}
		if (getExit()) {
			close(currClientSocket);
			break;
		}
		pthread_mutex_lock(&coutMutex);
		cout << "New Client is connected" << endl;
		pthread_mutex_unlock(&coutMutex);

		pthread_t *newThread = new pthread_t();

		clientCommunicationThreads.push_back(newThread);

		lastUsedClient = currClientSocket;

		int threadCreateResult = pthread_create(newThread, NULL, clientCommunicationThreadMain, (void *) this);

		if (threadCreateResult) {
			pthread_mutex_lock(&coutMutex);
			cout << "Error, thread creating failed" << endl;
			pthread_mutex_unlock(&coutMutex);

			removeFromVector(&clientCommunicationThreads, newThread);
		}
	}

	for (vector<pthread_t *>::iterator it = clientCommunicationThreads.begin(); it != clientCommunicationThreads.end(); ++it) {
		pthread_join(*(*it), NULL);
	}

	for (vector<pthread_t *>::iterator it = gameThreads.begin(); it != gameThreads.end(); ++it) {
		pthread_join(*(*it), NULL);
	}

	pthread_mutex_lock(&coutMutex);
	cout << "All done. All communications are closed!" << endl;
	pthread_mutex_unlock(&coutMutex);
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
		while (readSize == -1) {
			//Re-reading the message (timeout)
			readSize = recv(sender, buffer, BUFFER_SIZE, RECV_FLAGS);
		}
		if (readSize == 0) {
			//Client disconnection
			cout << "Client " << curr << " disconnected" << endl;
			return false;
		} else if (strcmp(endConnection.c_str(), buffer) == 0) {
			//Game ending
			cout << "Game ended!" << endl;
			return false;
		} else if (getVerbose()) {
			cout << buffer;
		}

		//Writing the message to the other client
		writeSize = send(reciever, buffer, strlen(buffer), SEND_FLAGS);
		while (writeSize == -1) {
			//Re-writing the message (timeout)
			writeSize = send(reciever, buffer, strlen(buffer), SEND_FLAGS);
		}

		if (writeSize != BUFFER_SIZE) {
			//The message received completely
			if (getVerbose()) {
				cout << endl;
			}
			return true;
		}
	}
	return true;
}

/***************************************
 * Function Name: handleCommand
 * The Input: socket id of a client
 * The Output: boolean value (true or false)
 * The Function Operation: handling the client's
 * command and returning if the operation succeeded
 **************************************/
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
		while (readSize == -1) {
			//Re-reading the message (timeout)
			readSize = recv(client, buffer, BUFFER_SIZE, RECV_FLAGS);
		}
		if (readSize <= 0) {
			//Client disconnected
			pthread_mutex_lock(&coutMutex);
			cout << "Client " << client << " disconnected" << endl;
			pthread_mutex_unlock(&coutMutex);
			return false;
		}

		msg.append(buffer);
		memset(buffer, 0, BUFFER_SIZE);

		if (readSize != BUFFER_SIZE) {
			break;
		}
	}
	if (getVerbose()) {
		pthread_mutex_lock(&coutMutex);
		cout << client << ": " << msg << endl;
		pthread_mutex_unlock(&coutMutex);
	}
	pair<string, vector<string> > cmd = extractCommand(msg);
	cmdManager.executeCommand(client, cmd.first, cmd.second);
	return true;
}

/***************************************
 * Function Name: sendMessageToClient
 * The Input: socket id of a client and a reference
 * to a message
 * The Output: boolean value
 * The Function Operation: sending a message
 * to the given client and returning true if succeeded,
 * otherwise false
 **************************************/
bool Server::sendMessageToClient(int client, string& msg) {
	int writeSize;
	writeSize = send(client, msg.c_str(), msg.length(), SEND_FLAGS);
	if (writeSize < 0) {
		//Error in writing
		pthread_mutex_lock(&coutMutex);
		cout << "Error writing to client " << client << endl;
		pthread_mutex_unlock(&coutMutex);
		return false;
	}
	return true;
}

/***************************************
 * Function Name: addThread
 * The Input: socket id of a client
 * The Output: no output
 * The Function Operation: adding a thread for
 * the given client
 **************************************/
void Server::addThread(int client) {
	pthread_t *newThread = new pthread_t();

	gameThreads.push_back(newThread);

	GameInfo *currGame = games.getGameInfo(client);

	lastUsedGame = currGame;

	int threadCreateResult = pthread_create(newThread, NULL, gameThreadMain, (void *) this);

	if (threadCreateResult) {
		pthread_mutex_lock(&coutMutex);
		cout << "Error, thread creating failed" << endl;
		pthread_mutex_unlock(&coutMutex);

		removeFromVector(&gameThreads, newThread);
		int other = currGame->getOtherClient(client);
		string endGame = string("END");
		sendMessageToClient(client, endGame);
		sendMessageToClient(other, endGame);
	}
}


/***************************************
 * Function Name: getVerbose
 * The Input: no input
 * The Output: boolean value
 * The Function Operation: returning
 * the value of the verbose
 **************************************/
bool Server::getVerbose() {
	pthread_mutex_lock(&verboseMutex);
	bool toReturn = verbose;
	pthread_mutex_unlock(&verboseMutex);
	return toReturn;
}

/***************************************
 * Function Name: getExit
 * The Input: no input
 * The Output: boolean value
 * The Function Operation: returning the
 * value of the exit boolean member
 **************************************/
bool Server::getExit() {
	pthread_mutex_lock(&serverExitMutex);
	bool toReturn = serverExit;
	pthread_mutex_unlock(&serverExitMutex);
	return toReturn;
}

/***************************************
 * Function Name: setExit
 * The Input: boolean value
 * The Output: no output
 * The Function Operation: updating the
 * value of the exit boolean member
 **************************************/
void Server::setExit(bool exit) {
	pthread_mutex_lock(&serverExitMutex);
	serverExit = exit;
	pthread_mutex_unlock(&serverExitMutex);
	if (exit) {
		games.interruptMatches();
	}
}

//Outsider Functions


/***************************************
 * Function Name: extractCommand
 * The Input: a reference to a message
 * The Output: a pair of a command and
 * a suitable vector of arguments
 * The Function Operation: extracting a command
 * based on the given message
 **************************************/
pair<string, vector<string> > extractCommand(string& msg) {
	string command;
	vector<string> args;
	string currentWord = "";
	bool foundCommand = false;

	if (msg.find(" ") == string::npos) {
		return make_pair(msg, args);
	}

	size_t index = 0;
	while ((index = msg.find(" ")) != string::npos) {
		currentWord = msg.substr(0, index);
		if (!foundCommand) {
			command = currentWord;
			foundCommand = true;
		} else {
			args.push_back(currentWord);
		}
		msg = msg.substr(index + 1);
	}
	args.push_back(msg);

	return make_pair(command, args);
}

/***************************************
 * Function Name: gameThreadMain
 * The Input: a pointer of an argument
 * The Output: NULL
 * The Function Operation: activating the main
 * thread of the game
 **************************************/
void *gameThreadMain(void *arg) {
	Server *theServer = (Server *) arg;
	GameInfo *currGame = theServer->lastUsedGame;

	int firstClient = currGame->getClientA();
	int secondClient = currGame->getClientB();

	bool ok = true;

	int currClient = firstClient;

	while (ok) {
		bool ok = theServer->handleCommand(currClient);
		if (!ok) {
			theServer->games.removeGame(currGame);
			return NULL;
		}
		if (currGame->getInterrupt() == true) {
			theServer->games.removeGame(currGame);
			return NULL;
		}
		currClient = (currClient == firstClient) ? secondClient : firstClient;
	}

	return NULL;
}

/***************************************
 * Function Name: clientCommunicationThreadMain
 * The Input: a pointer of an argument
 * The Output: NULL
 * The Function Operation: activating the main thread
 * of the client's communication
 **************************************/
void* clientCommunicationThreadMain(void* arg) {
	Server *theServer = (Server *) arg;
	int currClientSocket = theServer->lastUsedClient;

	//Handling the requests
	bool ok = true;
	while (ok) {
		if (theServer->getExit()) {
			close(currClientSocket);
			return NULL;
		}
		ok = theServer->handleCommand(currClientSocket);
		if (!ok || (theServer->games.getLastCommand() == GameSet::Start &&
					theServer->games.getLastCommandResult() == NO_ERROR_RESULT)) {
			ok = false;
		} else if (theServer->games.getLastCommand() == GameSet::Join &&
				   theServer->games.getLastCommandResult() == NO_ERROR_RESULT) {
			theServer->addThread(currClientSocket);
			ok = false;
		} else if (theServer->getExit()) {
			ok = false;
			close(currClientSocket);
		}
	}

	return NULL;
}

/***************************************
 * Function Name: exitThreadMain
 * The Input: a pointer of an argument
 * The Output: NULL
 * The Function Operation: closing the main
 * thread
 **************************************/
void* exitThreadMain(void* arg) {
	Server *theServer = (Server *) arg;

	string input = "";
	string toCompare = "exit";
	cin >> input;
	while (input != toCompare) {
		cin >> input;
	}
	theServer->setExit(true);
	pthread_mutex_lock(&theServer->coutMutex);
	cout << "Closing all communications, please wait." << endl;
	cout << "It may take up to 30 seconds" << endl;
	pthread_mutex_unlock(&theServer->coutMutex);

	return NULL;
}
