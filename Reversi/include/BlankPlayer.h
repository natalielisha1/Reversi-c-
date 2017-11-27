/*
 * BlankPlayer.h
 *
 *  Created on: Nov 24, 2017
 *      Author: ofek286
 */

#ifndef INCLUDE_BLANKPLAYER_H_
#define INCLUDE_BLANKPLAYER_H_

#include <vector>

#include "Player.h"

class BlankPlayer: public Player {
public:
	BlankPlayer(Board::Cell type);
	~BlankPlayer();
	virtual Point makeMove(std::vector<Point> *options, Point bestMove);
	virtual void sendMessage(const char *message);
};

#endif /* INCLUDE_BLANKPLAYER_H_ */
