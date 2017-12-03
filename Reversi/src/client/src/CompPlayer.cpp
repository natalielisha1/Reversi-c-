/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex3
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
Point CompPlayer::makeMove(vector<Point> *options, Point bestMove) {
	//Nothing right now...
	return bestMove;
}

/***************************************
 * Function Name: sendMessage
 * The Input: the message
 * The Output: nothing
 * The Function Operation: nothing
 **************************************/
void CompPlayer::sendMessage(const char *message) {
	//Do Nothing - computer can't receive messages
}
