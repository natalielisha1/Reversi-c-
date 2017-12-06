/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex3
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
	//The menu
	do {
		/*
		cout << "1 Vs 1 or Player Vs COM?" << endl;
		cout << "('H' for 1 Vs 1, 'C' for Player Vs COM): ";

		cin >> input;
		if (input == 'H') {
			input = 'h';
		} else if (input == 'C') {
			input = 'c';
		}
		if (input == 'c' || input == 'h') {
			break;
		}
		*/
		cout << "Welcome to Reversi!" << endl << endl;
		cout << "1. a human local player" << endl;
		cout << "2. an AI player" << endl;
		cout << "3. a remote player" << endl;

		cin >> input;
		if (input == '1') {
			input = HUMAN_PLAYER_IDENTIFIER;
			break;
		} else if (input == '2') {
			input = COMP_PLAYER_IDENTIFIER;
			break;
		} else if (input == '3') {
			input = REMOTE_PLAYER_IDENTIFIER;
			break;
		}
	} while (true);
	//Creating the game
	Game currGame = Game(HUMAN_PLAYER_IDENTIFIER, input);
	//Running the game
	currGame.run();
	return 0;
}
