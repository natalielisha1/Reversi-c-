/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex4
 **************************************/

#include "gtest/gtest.h"
#include "Point.h"
#include "Board.h"

using namespace std;

TEST(BoardTest, CheckUpForPut) {
	Board b = Board();

	//basic level
	b.putClean(Point(6,5), Board::X);
	b.putClean(Point(5,5), Board::X);
	b.putClean(Point(6,4), Board::O);
	b.putClean(Point(5,4), Board::O);

	if (b.put(Point(-2,-2), Board::X)) {
		throw "(-2,-2) doesn't exists, put wasn't supposed to succeed";
		exit(1);
	}

	if (!b.put(Point(3,3), Board::X)) {
		throw "put shouldn't fail to put (3,3)";
	} else if (b.getCell(Point(3,3)) == Board::X){
		//doNothing
	}

	//less basic level
	b.put(Point(5,5), Board::O);

	if (!b.put(Point(6,4), Board::X)) {
		throw "put failed to change (6,4) to X";
	} else if (b.getCell(Point(5,5)) != Board::O) {
		throw "put failed to change (5,5) to O";
	}
}


