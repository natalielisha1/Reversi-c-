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
						  	  	  	  	  	  verbose(false){
	pthread_mutex_init(&gamesMutex, NULL);
	pthread_mutex_init(&verboseMutex, NULL);
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
																		 verbose(verbose){
	pthread_mutex_init(&gamesMutex, NULL);
	pthread_mutex_init(&verboseMutex, NULL);
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

	//Waiting for the clients to connect
	cout << "Waiting for client connections..." << endl;

	while (true) {
		int currClientSocket;
		struct sockaddr_in currClient;
		socklen_t clientLen = sizeof(struct sockaddr_in);
		//Cleaning the client's info structure
		bzero((void *)&currClient, sizeof(currClient));

		//Connecting the current client
		currClientSocket = accept(serverSocket, (struct sockaddr *)&currClient, (socklen_t*)&clientLen);
		if (currClientSocket == -1) {
			//The first client's connection failed, so we crash
			cout << "Error on accept" << endl;
			continue;
		}

		//Handling the requests
		bool ok = true;
		while (ok) {
			ok = handleCommand(currClientSocket);
			if (!ok || (games.getLastCommand() == GameSet::Start &&
								 games.getLastCommandResult() == NO_ERROR_RESULT)) {
				ok = false;
			} else if (games.getLastCommand() == GameSet::Join &&
								games.getLastCommandResult() == NO_ERROR_RESULT) {
				addThread(currClientSocket);
				ok = false;
			}
		}
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
		} else if (getVerbose()) {
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
			if (getVerbose()) {
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
	if (getVerbose()) {
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

void Server::addThread(int client) {
	pthread_t *newThread = new pthread_t();

	gameThreads.push_back(newThread);

	GameInfo *currGame = games.getGameInfo(client);

//	pair<GameInfo *, Server *> arg;
//
//	arg = make_pair(currGame, this);

	lastUsedGame = currGame;

	int threadCreateResult = pthread_create(newThread, NULL, gameThreadMain, (void *) this);

	if (threadCreateResult) {
		cout << "Error, thread creating failed" << endl;

		removeFromVector(&gameThreads, newThread);
		int other = currGame->getOtherClient(client);
		string endGame = string("END");
		sendMessageToClient(client, endGame);
		sendMessageToClient(other, endGame);
	}
}

bool Server::getVerbose() {
	pthread_mutex_lock(&verboseMutex);
	bool toReturn = verbose;
	pthread_mutex_unlock(&verboseMutex);
	return toReturn;
}

//Outsider Functions
void *gameThreadMain(void *arg) {
//	pair<GameInfo *, Server *> fromArg;
//	fromArg = *(pair<GameInfo *, Server *> *) arg;
//
//	GameInfo *currGame = fromArg.first;

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
