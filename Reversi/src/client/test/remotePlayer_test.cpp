/*
 * remotePlayer_test.cpp
 *
 *  Created on: Dec 3, 2017
 *      Author: Natalie Elisha
 */

#include "Game.h"
#include "RemotePlayer.h"
#include "gtest/gtest.h"

TEST(RemotePlayerTest, makeMoverTester) {
	//creating a game, running it, and see how makeMove of RemotePlayer function
	Game game = Game('r', 'r');
	//steps that leads to dead end for O player
	//the game should be over and X wins
	game.put(Point(4,5), Board::X);
	game.put(Point(5,3), Board::O);
	game.put(Point(4,2), Board::X);
	game.put(Point(3,5), Board::O);
	game.put(Point(2,4), Board::X);
	game.put(Point(5,5), Board::O);
	game.put(Point(4,6), Board::X);
	game.put(Point(5,4), Board::O);
	game.put(Point(6,4), Board::X);

	game.setCurrentStatus(Game::InProgress);

	vector<Point> *tempOptions;
	Point bestMove;
	Point move = Point(-1, -1);
	//Calc'ing the moves available to O
	tempOptions = game.calcMoves(Board::O);
	bestMove = game.getBestMove(tempOptions, Board::O);
	//testing makeMove, should return -1,-1 as a point
	move = game.getOPlayer()->makeMove(tempOptions, bestMove);
	delete tempOptions;
	if (move != Point(-1,-1)) {
		throw runtime_error("something is wrong with the function makeMove");
	}
}

TEST(RemotePlayerTest, sendMessageTester) {

	RemotePlayer player1 = RemotePlayer(Board::X);
	RemotePlayer player2 = RemotePlayer(Board::O);

	Game game = Game('r', 'r');
	vector<Point> *tempOptions2, *tempOptions1;
	Point bestMove2, bestMove1;
	tempOptions2 = game.calcMoves(Board::O);
	bestMove2 = game.getBestMove(tempOptions2, Board::O);
	tempOptions1 = game.calcMoves(Board::X);
	bestMove1 = game.getBestMove(tempOptions1, Board::X);


	//first check, checking if it sends noMove when it should
	player1.sendMessage("X: It's your move");
	if (player2.makeMove(tempOptions2, bestMove2) != Point(-1,-1)) {
		throw runtime_error("something's wrong with sendMessage");
	}

	//second check, checking if it doesn't send noMove when it shouldn't
	player2.sendMessage("X: It's your move");
	if (player1.makeMove(tempOptions1, bestMove1) == Point(-1,-1)) {
		throw runtime_error("something's wrong with sendMessage");
	}

	delete tempOptions2;
	delete tempOptions1;
}



