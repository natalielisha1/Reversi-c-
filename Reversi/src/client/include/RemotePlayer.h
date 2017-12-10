/*
 * RemotePlayer.h
 *
 *  Created on: Dec 3, 2017
 *      Author: ofek286
 */

#ifndef REMOTEPLAYER_H_
#define REMOTEPLAYER_H_

#include <vector>
#include <algorithm>
#include <sstream>

#include "Player.h"
#include "Client.h"

class RemotePlayer: public Player {
public:
	RemotePlayer(Board::Cell type);
	~RemotePlayer();
	Client getClient();

	virtual Point makeMove(std::vector<Point> *options, Point bestMove);
	virtual void sendMessage(const char *message);
private:
	Client client;
};

#endif /* REMOTEPLAYER_H_ */
