/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex5
 **************************************/

#include "CompPlayer.h"
using namespace std;

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
 * The Input: options to put Cell, and the
 *  best move
 * The Output: the best move
 * The Function Operation: returning the
 *  best move
 **************************************/
Point CompPlayer::makeMove(vector<Point> *options, Point bestMove) {
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
