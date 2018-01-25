/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex7
 **************************************/

#include "CommandResult.h"

/***************************************
 * Function Name: CommandResult
 * The Input: no input
 * The Output: a CommandManager instance
 * The Function Operation: constructor for
 * CommandResult instances
 **************************************/
CommandResult::CommandResult(): status(false), command(None), result(NO_ERROR_RESULT) {
	//Nothing right now
}

/***************************************
 * Function Name: CommandResult
 * The Input: status - a boolean value
 * The Output: a CommandManager instance
 * The Function Operation: constructor for
 * CommandResult instances
 **************************************/
CommandResult::CommandResult(bool status): status(status), command(None), result(NO_ERROR_RESULT) {
	//Nothing right now
}

/***************************************
 * Function Name: CommandResult
 * The Input: status - a boolean value
 * 						command - a CommandOption
 * 						result - an integer
 * The Output: a CommandManager instance
 * The Function Operation: constructor for
 * CommandResult instances
 **************************************/
CommandResult::CommandResult(bool status, CommandOption command, int result): status(status),
																			  command(command),
																			  result(result){
	//Nothing right now
}

/***************************************
 * Function Name: getStatus
 * The Input: no input
 * The Output: a boolean value
 * The Function Operation: returning the value
 * of the status member, true or false
 **************************************/
bool CommandResult::getStatus() const {
	return status;
}

/***************************************
 * Function Name: getCommand
 * The Input: no input
 * The Output: a CommandOption
 * The Function Operation: returning the
 * current CommandOption
 **************************************/
CommandResult::CommandOption CommandResult::getCommand() const {
	return command;
}

/***************************************
 * Function Name: getResult
 * The Input: no input
 * The Output: an integer
 * The Function Operation: returning the
 * current value of result member
 **************************************/
int CommandResult::getResult() const {
	return result;
}
