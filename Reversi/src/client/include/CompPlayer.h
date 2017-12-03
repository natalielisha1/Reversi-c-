/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex3
 **************************************/

#ifndef COMPPLAYER_H_
#define COMPPLAYER_H_

#include "Player.h"
#include "Point.h"
#include <vector>

class CompPlayer: public Player {
public:
	CompPlayer(Board::Cell type);
	~CompPlayer();
	virtual Point makeMove(std::vector<Point> *options, Point bestMove);
	virtual void sendMessage(const char *message);
};

#endif /* COMPPLAYER_H_ */
