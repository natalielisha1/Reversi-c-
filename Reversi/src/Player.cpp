/***************************************
 * Student Name: Ofek Segal
 * Student ID: 315638288
 * Exercise Name: Ex2
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
