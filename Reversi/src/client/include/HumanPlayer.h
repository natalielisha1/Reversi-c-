/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex4
 **************************************/

#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_

#include <vector>
#include <iostream>
#include <stdio.h>
#include <limits>

#include "Tools.h"
#include "Player.h"

class HumanPlayer: public Player {
public:
	HumanPlayer(Board::Cell type);
	~HumanPlayer();

	virtual Point makeMove(std::vector<Point> *options, Point bestMove);
	virtual void sendMessage(const char *message);
};

#endif /* HUMANPLAYER_H_ */
