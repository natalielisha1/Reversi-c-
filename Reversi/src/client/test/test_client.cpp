/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex5
 **************************************/

#include "gtest/gtest.h"
#include "Client.h"

TEST(ClientTest, ConnectionWithServerChecks) {
	Client c1 = Client("127.0.0.1", 49942);
	Client c2 = Client("127.0.0.1", 52672);
	c1.connectToServer();
	c2.connectToServer();

	//checking connection from one server to another
	c1.sendMessage("hello client number 2");
	std::string buffer1 = c2.readMessage();
	if (buffer1 == "") {
		throw "readMessage does not function well, returns empty string";
	} else {
		std::string str = "";
		for (int i = 0; i < 21; i++) {
			str = str + buffer1[i];
		}
		if (buffer1 != "hello client number 2") {
			throw "readMessage does not function well, returns the wrong string/buffer";
		}
	}

	//checking connection from the other server to the first one
	c2.sendMessage("oh hello client number 1");
	std::string buffer2 = c1.readMessage();
	if (buffer2 == "") {
		throw "readMessage does not function well, returns empty string";
	} else {
		std::string str = "";
		for (int i = 0; i < 21; i++) {
			str = str + buffer2[i];
		}
		if (buffer2 != "oh hello client number 1") {
			throw "readMessage does not function well, returns the wrong string/buffer";
		}
	}

	c1.disconnect();
	c2.disconnect();
}
