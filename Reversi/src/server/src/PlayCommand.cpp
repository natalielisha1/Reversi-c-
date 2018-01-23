/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex7
 **************************************/
#include "PlayCommand.h"

using namespace std;

/***************************************
 * Function Name: PlayCommand (Constructor)
 * The Input: a reference to a game set
 * The Output: instance of PlayCommand
 * The Function Operation: currently nothing
 **************************************/
PlayCommand::PlayCommand() {
	games = GameSet::getInstance();
}

/***************************************
 * Function Name: ~PlayCommand (Destructor)
 * The Input: no input
 * The Output: no output
 * The Function Operation: currently nothing
 **************************************/
PlayCommand::~PlayCommand() {
	//Nothing right now
}

/***************************************
 * Function Name: execute
 * The Input: sender's socket id and a vector
 * of arguments
 * The Output: no output
 * The Function Operation: executing (playing)
 * accordingly to the command
 **************************************/
CommandResult PlayCommand::execute(int sender, vector<string> args) {
	if (args.size() == 2) {
		return games->playMatch(sender, args[0], args[1]);
	} else if (args.size() == 1) {
		return games->playMatch(sender, args[0]);
	}
}
