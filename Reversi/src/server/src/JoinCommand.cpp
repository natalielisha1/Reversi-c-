/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex7
 **************************************/

#include "JoinCommand.h"

using namespace std;

/***************************************
 * Function Name: joinCommand (Constructor)
 * The Input: a reference of a game set
 * The Output: joinCommand instance
 * The Function Operation: currently nothing
 **************************************/
JoinCommand::JoinCommand(){
	games = GameSet::getInstance();
}

/***************************************
 * Function Name: ~joinCommand (Destructor)
 * The Input: no input
 * The Output: no ouput
 * The Function Operation: currently nothing
 **************************************/
JoinCommand::~JoinCommand() {
	//Nothing right now
}

/***************************************
 * Function Name: execute
 * The Input: id socket of the sender and a vector
 * of arguments
 * The Output: no ouput
 * The Function Operation: adding the sender (a client)
 * to a match
 **************************************/
CommandResult JoinCommand::execute(int sender, vector<string> args) {
	return games->joinMatch(sender, args);
}
