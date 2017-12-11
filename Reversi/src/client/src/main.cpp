/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex4
 **************************************/

#include "Game.h"
#include <stdio.h>
#include <iostream>

using namespace std;

/***************************************
 * Function Name: main
 * The Input: no input
 * The Output: nothing
 * The Function Operation: running the
 *  game
 **************************************/
int main() {
	char input;
	//The menu
	do {
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
