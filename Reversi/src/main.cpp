/***************************************
 * Student Name: Ofek Segal
 * Student ID: 315638288
 * Exercise Name: Ex2
 **************************************/

#include "Game.h"
#include <stdio.h>
#include <iostream>

/***************************************
 * Function Name: main
 * The Input: no input
 * The Output: the empty board
 * The Function Operation: creating a
 *  board and printing it
 **************************************/
int main() {
	char input;
	do {
		cout << "1 Vs 1 or Player Vs COM?" << endl;
		cout << "('H' for 1 Vs 1, 'C' for Player Vs COM): ";
		//char dummy;
		cin >> input;// >> dummy;
		if (input == 'H') {
			input = 'h';
		} else if (input == 'C') {
			input = 'c';
		}
		if (input == 'c' || input == 'h') {
			break;
		}
	} while (true);
	//Creating the game
	Game currGame = Game(HUMAN_PLAYER_IDENTIFIER, input);
	//Running the game
	currGame.run();
	return 0;
}
