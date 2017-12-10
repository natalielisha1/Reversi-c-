/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex3
 **************************************/

#ifndef GAME_H_
#define GAME_H_

#include <vector>
#include <map>
#include <limits.h>

#include "Board.h"
#include "Point.h"
#include "Player.h"
#include "Tools.h"
#include "HumanPlayer.h"
#include "CompPlayer.h"
#include "BlankPlayer.h"
#include "RemotePlayer.h"

#define HUMAN_PLAYER_IDENTIFIER 'h'
#define COMP_PLAYER_IDENTIFIER 'c'
#define BLANK_PLAYER_IDENTIFIER 'b'
#define REMOTE_PLAYER_IDENTIFIER 'r'

class Game {
public:
	enum GameStatus { NotPlaying, InProgress, XWins, OWins, Tie };
	Game();
	Game(char xPlayerIdentifier, char oPlayerIdentifier);
	Game(const Game& other);
	~Game();
	void run();
	vector<Point> *calcMoves(Board::Cell cell);
	bool put(Point point, Board::Cell cell);
	void printBoard() const;
	Board*& getGameBoard();
	Point getBestMove(vector<Point> *options, Board::Cell cell);
	std::map<int, Point> rankOptions(std::vector<Point> *options, Board::Cell cell);
	GameStatus getCurrentStatus();
	void setCurrentStatus(GameStatus status);
	GameStatus checkWinning() const;
	Player*& getOPlayer();
	Player*& getXPlayer();

private:
	Board *gameBoard;
	Player *xPlayer;
	Player *oPlayer;
	vector<Point> *xLocations;
	vector<Point> *oLocations;
	GameStatus currStatus;
	bool checkMove(Board::Cell cell, Point point, Direction dir);
	bool checkMoveEmpty(Board::Cell cell, Point point, Direction dir);
	bool tryToPut(Board::Cell cell, Point point, Direction dir, std::vector<Point> *tempLocations);
};

#endif /* GAME_H_ */
