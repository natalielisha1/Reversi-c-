/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex5
 **************************************/

#include "ListGamesCommand.h"

using namespace std;

/***************************************
 * Function Name: ListGamesCommand (Constructor)
 * The Input: a reference of a game set
 * The Output: ListGamesCommand instance
 * The Function Operation: currently nothing
 **************************************/
ListGamesCommand::ListGamesCommand() {
	games = GameSet::getInstance();
}

/***************************************
 * Function Name: ~ListGameCommand (Destructor)
 * The Input: no input
 * The Output: no ouput
 * The Function Operation: currently nothing
 **************************************/
ListGamesCommand::~ListGamesCommand() {
	//Nothing right now
}

/***************************************
 * Function Name: execute
 * The Input: id socket of the sender and a vector
 * of arguments
 * The Output: no output
 * The Function Operation: listing the matches according
 * the given sender socket id and arguments
 **************************************/
CommandResult ListGamesCommand::execute(int sender, vector<string> args) {
	return games->listMatches(sender);
}
