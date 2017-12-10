/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex3
 **************************************/

#include "gtest/gtest.h"
#include "Game.h"
#include "Board.h"
#include "Point.h"
#include <stdexcept>

using namespace std;

TEST(GameTest, CheckUpsForPut) {
	Game game('b', 'b');

	//basic level
	game.getGameBoard()->putClean(Point(6,5), Board::X);
	game.getGameBoard()->putClean(Point(5,5), Board::X);
	game.getGameBoard()->putClean(Point(6,4), Board::O);
	game.getGameBoard()->putClean(Point(5,4), Board::O);

	if (!game.put(Point(3,3), Board::X)) {
		throw runtime_error("somehow put failed to put (3,3)");
	} else if (game.getGameBoard()->getCell(Point(4,4)) == Board::X){
		//doNothing
	} else {
		throw runtime_error("put (3,3) did not change the cell (4,4)");
	}

	//less basic level
	game.getGameBoard()->putClean(Point(7,6), Board::O);
	game.getGameBoard()->putClean(Point(6,5), Board::O);
	game.getGameBoard()->putClean(Point(7,4), Board::X);
	game.getGameBoard()->putClean(Point(6,4), Board::X);
	game.getGameBoard()->putClean(Point(5,4), Board::X);
	game.getGameBoard()->putClean(Point(3,5), Board::O);
	game.getGameBoard()->putClean(Point(4,5), Board::O);
	game.getGameBoard()->putClean(Point(5,5), Board::O);
	game.getGameBoard()->putClean(Point(5,6), Board::X);
	game.getGameBoard()->putClean(Point(5,5), Board::X);
	game.getGameBoard()->putClean(Point(6,5), Board::X);

	if (!game.put(Point(4,3), Board::O)) {
		throw runtime_error("put failed to put (4,3) as O somehow");
	} else if (game.getGameBoard()->getCell(Point(4,4)) != Board::O
			|| game.getGameBoard()->getCell(Point(5,4)) != Board::O
			|| game.getGameBoard()->getCell(Point(6,5)) != Board::O) {
		throw runtime_error("put didn't change one or more of the three cells");
	}
}


TEST(GameTest, NoMovesAvailable) {
	Game game('b', 'b'); //creating a game with two blank players
	game.put(Point(4,5), Board::X);
	game.put(Point(5,3), Board::O);
	game.put(Point(4,2), Board::X);
	game.put(Point(3,5), Board::O);
	game.put(Point(2,4), Board::X);
	game.put(Point(5,5), Board::O);
	game.put(Point(4,6), Board::X);
	game.put(Point(5,4), Board::O);
	game.put(Point(6,4), Board::X);
	vector<Point>* v = game.calcMoves(Board::O);
	if (!(v->size() == 0)) {
		throw runtime_error("WARNING. calcMoves doesn't function well when there "
				"are no options left to play");
	}

	if (!(game.getBestMove(v, Board::O).operator ==(Point(-1,-1)))) {
		throw runtime_error("WARNING. getBestMove doesn't function well when there "
				"are no options left to play");
	}

	map<int,Point> m = game.rankOptions(v, Board::O);
	if (!m.empty()) {
		throw runtime_error("WARNING. rankOptions does not function well when there are "
				"no options left for AI player");
	}

	delete v;
}

TEST(GameTest, ALotOfMovesAvailable) {
	Game game('b', 'b'); //creating a game with two blank players
	game.put(Point(2,3), Board::X);
	vector<Point>* vPoints1 = new vector<Point>();
	vPoints1->push_back(Point(2,2));
	vPoints1->push_back(Point(2,4));
	vPoints1->push_back(Point(4,2));

	map<int, Point> m = game.rankOptions(vPoints1, Board::O);
	int forCheck = 0;
  for (map<int, Point>::iterator i=m.begin(); i!=m.end(); ++i) {
	  if (i->first == 3) {
		  Point p = i->second;
		  if (p == Point(2,2) || p == Point(4,2)) {
			  forCheck = 1;
		  }
	  }
  }
  if (forCheck != 1) {
	  throw runtime_error("WARNING. trouble in function rankOptions in Game.cpp\n"
			  "the function can't calculate the rank of (3,3) and (5,3)");
  }

  game.put(Point(4,2), Board::O);
  game.put(Point(5,1), Board::X);
  game.put(Point(2,5), Board::O);
  game.put(Point(5,5), Board::X);
  game.put(Point(4,5), Board::O);
  game.put(Point(5,3), Board::X);
  game.put(Point(6,2), Board::O);
  game.put(Point(1,6), Board::X);
  vector<Point>* vPoints2 = new vector<Point>();
  vPoints2->push_back(Point(1,2));
  vPoints2->push_back(Point(1,3));
  vPoints2->push_back(Point(2,2));
  vPoints2->push_back(Point(3,1));
  vPoints2->push_back(Point(4,0));
  vPoints2->push_back(Point(4,1));
  vPoints2->push_back(Point(6,5));
  vPoints2->push_back(Point(6,6));
  vPoints2->push_back(Point(2,4));

  vector<Point>* vPoints3 = game.calcMoves(Board::O);
  for (vector<Point>::iterator it = vPoints3->begin(); it != vPoints3->end(); ++it) {
	  --(*it);
  }

  if (vPoints2->size() != vPoints3->size()) {
	  throw runtime_error("calcMoves - wrong size");
  	}
  bool notOK = false;
  bool innerFound = false;
  for (vector<Point>::iterator i3 = vPoints3->begin(); i3 != vPoints3->end(); ++i3) {
	  for (vector<Point>::iterator i2 = vPoints2->begin(); i2 != vPoints2->end(); ++i2) {
		  if (*i3 == *i2) {
			  innerFound = true;
		  	}

	    }
	  if (!innerFound) {
			notOK = true;
		}
	  innerFound = false;
    }
  //it's ok if it checks by value and not by order and value
  if (!notOK) {
	  //cout << "seems like caclMoves works just fine" << endl;
  } else {
	  throw runtime_error("error in calcMoves, function doesn't function well");
    }

  delete vPoints1;
  delete vPoints2;
  delete vPoints3;
}

