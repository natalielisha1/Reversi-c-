/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex5
 **************************************/

#include "BlankPlayer.h"

/***************************************
 * Function Name: BlankPlayer (Constructor)
 * The Input: the player's type
 * The Output: the new player
 * The Function Operation: nothing
 **************************************/
BlankPlayer::BlankPlayer(Board::Cell type): Player(type) {}


/***************************************
 * Function Name: ~CompPlayer (Destructor)
 * The Input: no input
 * The Output: no output
 * The Function Operation: nothing
 **************************************/
BlankPlayer::~BlankPlayer() {
	//Nothing
}

/***************************************
 * Function Name: makeMove
 * The Input: options to put Cell
 * The Output: the chosen option
 * The Function Operation: nothing
 **************************************/
Point BlankPlayer::makeMove(vector<Point> *options, Point bestMove) {
	//Returning nothing
	return Point(-1,-1);
}

/***************************************
 * Function Name: sendMessage
 * The Input: the message
 * The Output: nothing
 * The Function Operation: nothing
 **************************************/
void BlankPlayer::sendMessage(const char *message) {
	//Do Nothing
}
