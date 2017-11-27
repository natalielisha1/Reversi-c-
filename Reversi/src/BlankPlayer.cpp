/*
 * BlankPlayer.cpp
 *
 *  Created on: Nov 24, 2017
 *      Author: ofek286
 */

#include "BlankPlayer.h"

BlankPlayer::BlankPlayer(Board::Cell type): Player(type) {}

BlankPlayer::~BlankPlayer() {
	//Nothing
}

Point BlankPlayer::makeMove(vector<Point> *options, Point bestMove) {
	//Nothing
	return Point(-1,-1);
}

void BlankPlayer::sendMessage(const char *message) {
	//Do Nothing
}
