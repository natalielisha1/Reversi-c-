/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex5
 **************************************/
#include "GameSet.h"
#include "gtest/gtest.h"
using namespace std;

TEST(GameSetTest, StartCloseTesting) {
	vector<string> args;
	GameSet info = GameSet();
	string gameName = "gameMatch";
	int ofek_socket = 49154;

	//case of no args
	info.startNewMatch(ofek_socket, args);
	if (info.getLastCommand() != GameSet::Start || info.getLastCommandResult() != -2) {
		throw runtime_error("startNewMatch fails in case there are no args");
	}

	info.closeMatch(ofek_socket, args);
	if (info.getLastCommandResult() != -2 || info.getLastCommand() != GameSet::Close) {
		throw runtime_error("closeMatch fails in case there are no args");
	}

	//normal case
	args.push_back(gameName);
	info.startNewMatch(ofek_socket, args);
	if (info.getLastCommand() != GameSet::Start || info.getLastCommandResult() != 1) {
		throw runtime_error("startNewMatch fails adding a new match");
	}

	//in case there's already a game with the same name
	info.startNewMatch(ofek_socket, args);
	if (info.getLastCommand() != GameSet::Start || info.getLastCommandResult() != -1) {
		throw runtime_error("startNewMatch fails in case the name already exists");
	}

	info.closeMatch(ofek_socket, args);
	if (info.getLastCommand() != GameSet::Close || info.getLastCommandResult() != 1) {
		throw runtime_error("closeMatch fails closing an existing match");
	}

	//testing getGameInfo function
	GameInfo thisGameInfo = info.getGameInfo(ofek_socket);
	if (thisGameInfo.getGameName() != gameName || thisGameInfo.getClientA() != ofek_socket) {
		throw runtime_error("error - getGameInfo fails");
	}
}

TEST(GameSetTest, DebugMessageTesting) {
	vector<string> args1, args2, args3;
	GameSet info = new GameSet();

	//in case there are no arguments
	info.debugMessage(49554, args1);
	if (info.getLastCommand() != GameSet::Debug || info.getLastCommandResult() != 1) {
		throw runtime_error("debugMessage fails in case of no args");
	}

	//in case there are arguments
	string str0 = "find";
	string str1 = "hello world";
	string str2 = "start thisGame";

	//in case args.size < 2
	args1.push_back(str1);
	info.debugMessage(49554, args1);
	if (info.getLastCommand() != GameSet::Debug || info.getLastCommandResult() != -2) {
		throw runtime_error("debugMessage fails in case there's one argument");
	}

	//in case there is no "find"
	args1.push_back(str2);
	if (info.getLastCommand() != GameSet::Debug || info.getLastCommandResult() != -2) {
		throw runtime_error("debugMessage fails in case there's two arguments, but no 'find' ");
	}


	//in case there is "find" and args.size>=2, assuming startMatch command works
	//in case the game does not exist
	args2.push_back(str0);
	args2.push_back(str1);
	args2.push_back(str2);
	if (info.getLastCommand() != GameSet::Debug || info.getLastCommandResult() != -6) {
		throw runtime_error("debugMessage fails in case the game does not exist");
	}

	//in case the game exists
	args3.push_back(str1);
	args3.push_back(str2);
	info.startNewMatch(49554, args2);
	if (info.getLastCommand() != GameSet::Debug || info.getLastCommandResult() != 1) {
		throw runtime_error("debugMessage fails in case the game exists");
	}

}

TEST(GameSetTest, JoinCommandTesting) {
	vector<string> args, args2;
		GameSet info = GameSet();
		string gameName = "firstMatch";
		int natalie_socket = 23751;
		int linoy_socket = 9484;
		GameInfo gameInfo = GameInfo();
		gameInfo.setGameName(gameName);
		gameInfo.setStatus(GameInfo::XWaiting);
		gameInfo.setClientA(84373);

		//case of no args
		info.startNewMatch(natalie_socket, args);
		if (info.getLastCommand() != GameSet::Join || info.getLastCommandResult() != -2) {
			throw runtime_error("joinMatch fails in case there are no args");
		}

		//normal case

		//assuming startNewMatch is working
		args.push_back(gameName);
		info.startNewMatch(84373, args);

		info.startNewMatch(natalie_socket, args);
		if (info.getLastCommand() != GameSet::Join || info.getLastCommandResult() != 1) {
			throw runtime_error("joinMatch fails joining another player to the match");
		}

		info.joinMatch(linoy_socket, args);
		if (info.getLastCommand() != GameSet::Join || info.getLastCommandResult() != -7) {
			throw runtime_error("joinMatch fails in case the match is full");
		}

		args2.push_back("linoy'sGame");
		info.joinMatch(linoy_socket, args2);
		if (info.getLastCommand() != GameSet::Join || info.getLastCommandResult() != -6) {
			throw runtime_error("joinMatch fails in case the game does not exists");
		}
}
//endOfTests

