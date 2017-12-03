/*
 * RemotePlayer.cpp
 *
 *  Created on: Dec 3, 2017
 *      Author: ofek286
 */

#include "RemotePlayer.h"

RemotePlayer::RemotePlayer(Board::Cell type): Player(type), client("127.0.0.1", 8787) {
	//TODO: WRITE

}

RemotePlayer::~RemotePlayer() {
	//TODO: WRITE
}

Point RemotePlayer::makeMove(std::vector<Point>* options, Point bestMove) {
	//TODO: WRITE

	return Point(-1,-1);
}

void RemotePlayer::sendMessage(const char* message) {
	//TODO: WRITE
}
