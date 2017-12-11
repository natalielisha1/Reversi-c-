/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex4
 **************************************/

#ifndef BLANKPLAYER_H_
#define BLANKPLAYER_H_

#include <vector>

#include "Player.h"

class BlankPlayer: public Player {
public:
	BlankPlayer(Board::Cell type);
	~BlankPlayer();

	virtual Point makeMove(std::vector<Point> *options, Point bestMove);
	virtual void sendMessage(const char *message);
};

#endif /* BLANKPLAYER_H_ */
