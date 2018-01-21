/*
 * CommandResult.h
 *
 *  Created on: Jan 20, 2018
 *      Author: ofek286
 */

#ifndef COMMANDRESULT_H_
#define COMMANDRESULT_H_

//Predefined error results
#define NO_ERROR_RESULT 1
#define ERROR_GAME_EXISTS_RESULT -1
#define ERROR_NO_ARGS_RESULT -2
#define ERROR_INVALID_CLIENT_RESULT -3
#define ERROR_GAME_NOT_PLAYING_RESULT -4
#define ERROR_FAKE_NO_MOVE_RESULT -5
#define ERROR_GAME_DOES_NOT_EXIST_RESULT -6
#define ERROR_GAME_FULL_RESULT -7

class CommandResult {
public:
	enum CommandOption {Debug, Start, Join, Play, Close, List, None};

	CommandResult();
	CommandResult(bool status);
	CommandResult(bool status, CommandOption command, int result);

	bool getStatus() const;
	CommandOption getCommand() const;
	int getResult() const;

private:
	bool status;
	CommandOption command;
	int result;
};

#endif /* COMMANDRESULT_H_ */
