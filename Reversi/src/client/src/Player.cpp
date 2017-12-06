/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex3
 **************************************/

#include "Player.h"

/***************************************
 * Function Name: Player (Constructor)
 * The Input: the player's type
 * The Output: the new player
 * The Function Operation: assigning
 *  variables
 **************************************/
Player::Player(Board::Cell type): type(type) {}

/***************************************
 * Function Name: Player (Constructor)
 * The Input: no input
 * The Output: the new player
 * The Function Operation: assigning
 *  variables
 **************************************/
Player::Player(): type(Board::Empty) {}

Board::Cell Player::getType() const {
	return type;
}

void Player::setType(Board::Cell newType) {
	type = newType;
}
