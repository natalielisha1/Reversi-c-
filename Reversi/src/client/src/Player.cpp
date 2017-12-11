/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex4
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

/***************************************
 * Function Name: getType
 * The Input: no input
 * The Output: the player's type
 * The Function Operation: returning
 *  the type
 **************************************/
Board::Cell Player::getType() const {
	return type;
}

/***************************************
 * Function Name: setType
 * The Input: the new type
 * The Output: nothing
 * The Function Operation: setting the
 *  type
 **************************************/
void Player::setType(Board::Cell newType) {
	type = newType;
}
