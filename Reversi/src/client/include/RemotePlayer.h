/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex4
 **************************************/

#ifndef REMOTEPLAYER_H_
#define REMOTEPLAYER_H_

#include <vector>
#include <algorithm>
#include <sstream>

#include "Player.h"
#include "Client.h"
#include "ToolsForStrings.h"

class RemotePlayer: public Player {
public:
	RemotePlayer(Board::Cell type);
	~RemotePlayer();

	Client getClient() const;

	virtual Point makeMove(std::vector<Point> *options, Point bestMove);
	virtual void sendMessage(const char *message);
private:
	Client client;
};

#endif /* REMOTEPLAYER_H_ */
