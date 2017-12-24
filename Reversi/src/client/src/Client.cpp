/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex4
 **************************************/

#include "Client.h"
using namespace std;

/***************************************
 * Function Name: Client (Constructor)
 * The Input: nothing
 * The Output: the client instance
 * The Function Operation: initializing
 *  the client from config file
 **************************************/
Client::Client(): clientSocket(0), gameName("") {
	//Reading the config file and applying the config
	ifstream serverConfig("server_address.txt");
	serverConfig >> serverIP;
	serverPort = 0;
	serverConfig >> serverPort;
	//Closing the file
	serverConfig.close();
}

/***************************************
 * Function Name: Client (Constructor)
 * The Input: the server's ip and port
 * The Output: the client instance
 * The Function Operation: initializing
 *  the client
 **************************************/
Client::Client(string &serverIP, int serverPort): serverIP(serverIP), serverPort(serverPort), clientSocket(0), gameName("") {
	//Nothing right now

}

/***************************************
 * Function Name: ~Client (Destructor)
 * The Input: no input
 * The Output: no output
 * The Function Operation: nothing
 **************************************/
Client::~Client() {
	//Nothing right now
}

/***************************************
 * Function Name: connectToServer
 * The Input: no input
 * The Output: nothing
 * The Function Operation: connecting to
 *  the server
 **************************************/
void Client::connectToServer() {
	//Creating a socket pointer
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket < 0) {
		//The socket wasn't created, so we crash
		throw runtime_error("Error opening socket");
	}
	//Cleaning the structure for the server address
	bzero((char *)&serverAddress, sizeof(serverAddress));
	//Preparing the server address structure
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr(serverIP.c_str());
	serverAddress.sin_port = htons(serverPort);
	//Establishing a connection with the server
	if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
		//The connection failed, so we crash
		throw runtime_error("Error connecting to server");
	}
	//The server is connected
	cout << "Connected to server" << endl;
}

/***************************************
 * Function Name: disconnect
 * The Input: no input
 * The Output: nothing
 * The Function Operation: disconnecting
 *  from the server
 **************************************/
void Client::disconnect() {
	close(clientSocket);
}

/***************************************
 * Function Name: sendMessage
 * The Input: the message
 * The Output: the socket's response
 * The Function Operation: sending the
 *  message
 **************************************/
int Client::sendMessage(const char *msg) {
	return send(clientSocket, msg, strlen(msg), SEND_FLAGS);
}

/***************************************
 * Function Name: readMessage
 * The Input: no input
 * The Output: the message
 * The Function Operation: receiving the
 *  message and returning it
 **************************************/
string Client::readMessage() {
	//Preparing the string to return
	string toReturn = string("");
	//Creating a buffer
	char buffer[BUFFER_SIZE] = {0};
	//Creating a var to keep the socket response
	int readSize;
	while (true) {
		//Receiving the message
		if ((readSize = recv(clientSocket, buffer, BUFFER_SIZE - 1, RECV_FLAGS)) > 0) {
			//Adding the buffer to the string
			toReturn.append(buffer);
		}
		if (readSize != BUFFER_SIZE) {
			//If the message is over, return it
			return toReturn;
		}
		for (int i = 0; i < BUFFER_SIZE; i++) {
			buffer[i] = '\0';
		}
	}
}

string Client::readShortMessage() {
	//Preparing the string to return
	string toReturn = string("");
	//Creating a buffer
	char buffer[SHORT_BUFFER_SIZE] = {0};
	//Creating a var to keep the socket response
	int readSize;
	//Receiving the message
	if ((readSize = recv(clientSocket, buffer, SHORT_BUFFER_SIZE - 1, RECV_FLAGS)) > 0) {
		//Adding the buffer to the string
		toReturn.append(buffer);
	}
	return toReturn;
}


/***************************************
 * Function Name: waitForCue (Experimental)
 * The Input: no input
 * The Output: nothing
 * The Function Operation: waiting to receive
 *  cue
 **************************************/
void Client::waitForCue() {
	//Creating strings to compare the messages to
	string cueX = string("X: It's your move");
	string cueO = string("O: It's your move");
	//Creating a buffer
	char buffer[BUFFER_SIZE] = {0};
	//Creating a var to keep the socket response
	int readSize;
	while (true) {
		//Receiving the message
		if ((readSize = recv(clientSocket, buffer, BUFFER_SIZE, RECV_FLAGS)) > 0) {
			//Comparing the cues to the buffer
			if (strcmp(cueX.c_str(), buffer) == 0) {
				return;
			} else if (strcmp(cueO.c_str(), buffer) == 0) {
				return;
			}
		}
	}
}

/***************************************
 * Function Name: getOrder
 * The Input: no input
 * The Output: the connection order
 * The Function Operation: waiting to receive
 *  order and returning it
 **************************************/
int Client::getOrder() {
	//Creating strings to compare the messages to
	string first = string("1");
	string second = string("2");
	//Creating a buffer
	char buffer[REALLY_SHORT_BUFFER_SIZE] = {0};
	//Creating a var to keep the socket response
	int readSize;
	while (true) {
		//Receiving the message
		if ((readSize = recv(clientSocket, buffer, REALLY_SHORT_BUFFER_SIZE - 1, RECV_FLAGS)) > 0) {
			//Comparing the strings to the buffer
			if (strcmp(first.c_str(), buffer) == 0) {
				return 1;
			} else if (strcmp(second.c_str(), buffer) == 0) {
				return 2;
			}
		}
	}
	return -1;
}

string Client::genUniqueGameIdentifier() {
	string gameID = "OS";

	char *toStringResult;

	time_t now = time(0);

	tm *ltm = localtime(&now);

	toStringResult = myToString(ltm->tm_hour);
	if (strlen(toStringResult) == 1) {
		gameID.append("0");
	}
	gameID.append(toStringResult);
	delete[] toStringResult;

	toStringResult = myToString(ltm->tm_min);
	if (strlen(toStringResult) == 1) {
		gameID.append("0");
	}
	gameID.append(toStringResult);
	delete[] toStringResult;

	toStringResult = myToString(ltm->tm_sec);
	if (strlen(toStringResult) == 1) {
		gameID.append("0");
	}
	gameID.append(toStringResult);
	delete[] toStringResult;

	gameID.append("NE");

	gameName = gameID;
	return gameID;
}

const std::string& Client::getGameName() const {
	return gameName;
}

void Client::setGameName(const std::string& gameName) {
	this->gameName = gameName;
}
