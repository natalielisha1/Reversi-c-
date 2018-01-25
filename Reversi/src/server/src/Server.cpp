/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex7
 **************************************/

#include "Server.h"
using namespace std;

void *exitThreadMain(void *arg);

/***************************************
 * Function Name: Server (Constructor)
 * The Input: nothing
 * The Output: the server instance
 * The Function Operation: initializing
 *  the server from config file
 **************************************/
Server::Server(): serverSocket(0) {
	//Reading the config file and applying the config
	ifstream serverConfig("server_port.txt");
	if (!serverConfig.is_open()) {
		throw runtime_error("File not opening");
	}
	port = 0;
	serverConfig >> port;

	//Closing the file
	serverConfig.close();

	//Getting the singletons
	VerboseController::initialize();
	this->verbose = VerboseController::getInstance(false);

	CommandsManager::initialize();
	this->cmdManager = CommandsManager::getInstance();

	ThreadPool::initialize();
	this->threadPool = ThreadPool::getInstance(MAX_THREADS);

	ExitController::initialize();
	this->exitController = ExitController::getInstance();
}

/***************************************
 * Function Name: Server (Constructor)
 * The Input: verbose flag
 * The Output: the server instance
 * The Function Operation: initializing
 *  the server from config file
 **************************************/
Server::Server(bool verbose): serverSocket(0){
	//Reading the config file and applying the config
	ifstream serverConfig("server_port.txt");
	if (!serverConfig.is_open()) {
		throw runtime_error("File not opening");
	}
	port = 0;
	serverConfig >> port;

	//Closing the file
	serverConfig.close();

	//Getting the singletons
	VerboseController::initialize();
	this->verbose = VerboseController::getInstance(verbose);

	CommandsManager::initialize();
	this->cmdManager = CommandsManager::getInstance();

	ThreadPool::initialize();
	this->threadPool = ThreadPool::getInstance(MAX_THREADS);

	ExitController::initialize();
	this->exitController = ExitController::getInstance();
}

/***************************************
 * Function Name: Server (Constructor)
 * The Input: the port
 * The Output: the server instance
 * The Function Operation: initializing
 *  the server from port input
 **************************************/
Server::Server(int port): port(port), serverSocket(0){
	//Getting the singletons
	VerboseController::initialize();
	this->verbose = VerboseController::getInstance(false);

	CommandsManager::initialize();
	this->cmdManager = CommandsManager::getInstance();

	ThreadPool::initialize();
	this->threadPool = ThreadPool::getInstance(MAX_THREADS);

	ExitController::initialize();
	this->exitController = ExitController::getInstance();
}

/***************************************
 * Function Name: Server (Constructor)
 * The Input: the port and verbose flag
 * The Output: the server instance
 * The Function Operation: initializing
 *  the server from port input
 **************************************/
Server::Server(int port, bool verbose): port(port), serverSocket(0){
	//Getting the singletons
	VerboseController::initialize();
	this->verbose = VerboseController::getInstance(verbose);

	CommandsManager::initialize();
	this->cmdManager = CommandsManager::getInstance();

	ThreadPool::initialize();
	this->threadPool = ThreadPool::getInstance(MAX_THREADS);

	ExitController::initialize();
	this->exitController = ExitController::getInstance();
}

/***************************************
 * Function Name: ~Server (Destructor)
 * The Input: no input
 * The Output: no output
 * The Function Operation: nothing
 **************************************/
Server::~Server() {
	//Deleting the singletons
	VerboseController::deleteInstance();
	CommandsManager::deleteInstance();
	ExitController::deleteInstance();

	cout << "All done. All communications are closed!" << endl;
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

	//Creating the 'listen to "exit"' thread
	int exitThreadResult = pthread_create(&exitThread, NULL, exitThreadMain, (void *) this);
	if (exitThreadResult) {
		cout << "Exit thread creation failed, exiting" << endl;
		return;
	} else {
		cout << "Enter 'exit' to close the server" << endl;
	}

	//Waiting for the clients to connect
	verbose->lockCout();
	cout << "Waiting for client connections..." << endl;
	verbose->unlockCout();

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
				verbose->lockCout();
				cout << "Client accept timeout, retrying.." << endl;
				verbose->unlockCout();
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
		verbose->lockCout();
		cout << "New Client is connected" << endl;
		verbose->unlockCout();

		//Creating a new task for the new client
		long socketAsLong = (long) currClientSocket;
		threadPool->addTask(new ClientRequestsTask((void *) socketAsLong));
	}

	//Waiting for the 'listen to "exit"' thread to finish
	pthread_join(exitThread, NULL);
}

/***************************************
 * Function Name: stop
 * The Input: no input
 * The Output: no output
 * The Function Operation: closing the
 *  socket
 **************************************/
void Server::stop() {
	//Stopping the thread pool
	ThreadPool::deleteInstance();

	//Closing the clients
	for (vector<int>::iterator it = connectedClients.begin(); it != connectedClients.end(); ++it) {
		close(*it);
	}

	//Closing the socket
	close(serverSocket);
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
		verbose->lockCout();
		cout << "Error writing to client " << client << endl;
		verbose->unlockCout();
		return false;
	}
	return true;
}

/***************************************
 * Function Name: getVerbose
 * The Input: no input
 * The Output: boolean value
 * The Function Operation: returning
 * the value of the verbose
 **************************************/
bool Server::getVerbose() {
	return verbose->getVerbose();
}

/***************************************
 * Function Name: getExit
 * The Input: no input
 * The Output: boolean value
 * The Function Operation: returning the
 * value of the exit boolean member
 **************************************/
bool Server::getExit() {
	return exitController->getExit();
}

/***************************************
 * Function Name: setExit
 * The Input: boolean value
 * The Output: no output
 * The Function Operation: updating the
 * value of the exit boolean member
 **************************************/
void Server::setExit() {
	exitController->setExit();
	threadPool->terminate();
}

//Outsider Functions

/***************************************
 * Function Name: exitThreadMain
 * The Input: a pointer of an argument
 * The Output: NULL
 * The Function Operation: the main function
 * of the "exit" thread
 **************************************/
void *exitThreadMain(void *arg) {
	Server *theServer = (Server *) arg;

	string input = "";
	string toCompare = "exit";
	cin >> input;
	while (input != toCompare) {
		cin >> input;
	}
	theServer->setExit();
	theServer->verbose->lockCout();
	cout << "Closing all communications, please wait." << endl;
	cout << "It may take up to " << SOCKET_TIMEOUT << " seconds" << endl;
	theServer->verbose->unlockCout();

	return NULL;
}
