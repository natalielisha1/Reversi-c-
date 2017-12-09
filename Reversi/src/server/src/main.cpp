#include <iostream>
#include "Server.h"

using namespace std;

int main() {
	Server server = Server();
	try {
		server.start();
	} catch (const char *msg) {
		cout << "Cannot start server. Reason: " << msg << endl;
		return -1;
	}
	server.stop();
	return 0;
}
