/***************************************
 * Student Name: Ofek Segal
 * Student ID: 315638288
 * Exercise Name: Ex2
 **************************************/

#include "CompPlayer.h"

/***************************************
 * Function Name: CompPlayer (Constructor)
 * The Input: the player's type
 * The Output: the new player
 * The Function Operation: nothing
 **************************************/
CompPlayer::CompPlayer(Board::Cell type): Player(type) {}

/***************************************
 * Function Name: ~CompPlayer (Destructor)
 * The Input: no input
 * The Output: no output
 * The Function Operation: nothing
 **************************************/
CompPlayer::~CompPlayer() {
	// Nothing right now
}

/***************************************
 * Function Name: makeMove
 * The Input: options to put Cell
 * The Output: the chosen option
 * The Function Operation: nothing
 **************************************/
Point CompPlayer::makeMove(vector<Point> *options) {
	//Nothing right now...
	return Point(-1,-1);
}
