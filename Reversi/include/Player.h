/***************************************
 * Student Name: Ofek Segal
 * Student ID: 315638288
 * Exercise Name: Ex2
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
	virtual Point makeMove(vector<Point> *options) = 0;
protected:
	Board::Cell type;
};

#endif /* PLAYER_H_ */
