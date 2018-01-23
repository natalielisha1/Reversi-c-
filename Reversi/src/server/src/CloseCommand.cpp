/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex7
 **************************************/

#include "CloseCommand.h"

using namespace std;

/***************************************
 * Function Name: CloseCommand (Constructor)
 * The Input: reference to a gameSet
 * The Output: a closeCommand instance
 * The Function Operation: currently nothing
 **************************************/
CloseCommand::CloseCommand() {
	games = GameSet::getInstance();
}

/***************************************
 * Function Name: CloseCommand (Destructor)
 * The Input: no input
 * The Output: no output
 * The Function Operation: currently nothing
 **************************************/
CloseCommand::~CloseCommand() {
	//Nothing right now
}

/***************************************
 * Function Name: execute
 * The Input: the sender, and the args
 * The Output: no output
 * The Function Operation: closing the
 *			   game
 **************************************/
CommandResult CloseCommand::execute(int sender, vector<string> args) {
	return games->closeMatch(sender, args);
}
