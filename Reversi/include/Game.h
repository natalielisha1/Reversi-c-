/***************************************
 * Student Name: Ofek Segal
 * Student ID: 315638288
 * Exercise Name: Ex2
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

#define HUMAN_PLAYER_IDENTIFIER 'h'
#define COMP_PLAYER_IDENTIFIER 'c'

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
private:
	Board *gameBoard;
	Player *xPlayer;
	Player *oPlayer;
	vector<Point> *xLocations;
	vector<Point> *oLocations;
	GameStatus currStatus;
	bool checkMove(Board::Cell cell, Point point, Direction dir);
	bool checkMoveEmpty(Board::Cell cell, Point point, Direction dir);
	GameStatus checkWinning() const;
	bool tryToPut(Board::Cell, Point point, Direction dir, std::vector<Point> *tempLocations);
	std::map<int, Point> rankOptions(std::vector<Point> *options, Board::Cell cell);
	Point getBestMove(vector<Point> *options, Board::Cell cell);
};

#endif /* GAME_H_ */
