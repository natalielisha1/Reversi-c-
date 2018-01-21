/*
 * CommandResult.cpp
 *
 *  Created on: Jan 20, 2018
 *      Author: ofek286
 */

#include "CommandResult.h"

CommandResult::CommandResult(): status(false), command(None), result(NO_ERROR_RESULT) {
	//Nothing right now
}

CommandResult::CommandResult(bool status): status(status), command(None), result(NO_ERROR_RESULT) {
	//Nothing right now
}

CommandResult::CommandResult(bool status, CommandOption command, int result): status(status),
																			  command(command),
																			  result(result){
	//Nothing right now
}

bool CommandResult::getStatus() const {
	return status;
}

CommandResult::CommandOption CommandResult::getCommand() const {
	return command;
}

int CommandResult::getResult() const {
	return result;
}
