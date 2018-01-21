/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex5
 **************************************/

#include <iostream>
#include "Server.h"

using namespace std;

/***************************************
 * Function Name: main
 * The Input: no input
 * The Output: nothing
 * The Function Operation: running the
 *  server
 **************************************/
int main(int argc, char *argv[]) {
	bool verbose = false;
	if (argc > 1) {
		string verboseStr = string(argv[1]);
		if (verboseStr == "-v" || verboseStr == "-V") {
			verbose = true;
		}
	}
	//Creating the server
	Server server = Server(verbose);
	try {
		//Running the server
		server.start();

		//Stopping the server
		server.stop();
	} catch (const char *msg) {
		//Catching an error
		cout << "Cannot start server. Reason: " << msg << endl;
		return -1;
	}
	return 0;
}
