/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex3
 **************************************/

#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include "Point.h"
#include "Board.h"
using namespace std;

class Player {
public:
	Player();
	Player(Board::Cell type);
	virtual ~Player() {};
	virtual Point makeMove(vector<Point> *options, Point bestMove) = 0;
	virtual void sendMessage(const char *message) = 0;
protected:
	Board::Cell type;
};

#endif /* PLAYER_H_ */