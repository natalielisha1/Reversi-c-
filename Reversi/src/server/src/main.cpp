/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex4
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
int main() {
	//Creating the server
	Server server = Server();
	try {
		//Running the server
		server.start();
	} catch (const char *msg) {
		//Catching an error
		cout << "Cannot start server. Reason: " << msg << endl;
		return -1;
	}
	//Stopping the server
	server.stop();
	return 0;
}
