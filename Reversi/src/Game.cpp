/***************************************
 * Student Name: Ofek Segal
 * Student ID: 315638288
 * Exercise Name: Ex2
 **************************************/

#include "Game.h"
using namespace std;

/***************************************
 * Function Name: Game (Constructor)
 * The Input: no input
 * The Output: the game instance
 * The Function Operation: initializing
 *  the Cell lists, the board, and the
 *  players
 **************************************/
Game::Game() {
	xLocations = new vector<Point>();
	oLocations = new vector<Point>();

	gameBoard = new Board(xLocations, oLocations);

	xPlayer = new HumanPlayer(Board::X);
	oPlayer = new HumanPlayer(Board::O);

	currStatus = NotPlaying;
}

/***************************************
 * Function Name: ~Game (Destructor)
 * The Input: no input
 * The Output: no output
 * The Function Operation: freeing
 *  memory
 **************************************/
Game::~Game() {
	delete xPlayer;
	delete oPlayer;
	delete gameBoard;
	delete xLocations;
	delete oLocations;
}

/***************************************
 * Function Name: run
 * The Input: no input
 * The Output: no output
 * The Function Operation: running the
 *  game
 **************************************/
void Game::run() {
	//Starting the game
	if (currStatus == NotPlaying) {
		currStatus = InProgress;
	}
	//Temp variables to use later
	bool toCheckOther = false;
	Point move = Point(-1, -1);

	//While the game is running:
	while (currStatus == InProgress) {
		/*
		 * A temp variable to hold
		 * the options to place Cells
		 */
		vector<Point> *tempOptions;
		//Printing the board, and letting X play
		cout << "Current board:" << endl << endl;
		gameBoard->printBoard();
		if (move != Point(-1,-1)) {
			cout << "O played ";
			move++;//.deAlignToPrint();
			move.printPoint();
			cout << endl << endl;
		}
		cout << "X: It's your move" << endl;
		//Calc'ing the moves available to X
		tempOptions = calcMoves(Board::X);
		//Letting him choose
		move = xPlayer->makeMove(tempOptions);
		delete tempOptions;
		if (move == Point(-1,-1)) {
			if (toCheckOther) {
				currStatus = checkWinning();
				break;
			} else {
				toCheckOther = true;
			}
		//If he chose something, then it will be put
		} else if (toCheckOther) {
			toCheckOther = false;
			put(move, Board::X);
		} else {
			put(move, Board::X);
		}
		//Printing the board, and letting O play
		cout << "Current board:" << endl << endl;
		gameBoard->printBoard();
		if (move != Point(-1,-1)) {
			cout << "X played ";
			move++;//.deAlignToPrint();
			move.printPoint();
			cout << endl << endl;
		}
		cout << "O: It's your move" << endl;
		//Calc'ing the moves available to O
		tempOptions = calcMoves(Board::O);
		//Letting him choose
		move = oPlayer->makeMove(tempOptions);
		delete tempOptions;
		if (move == Point(-1,-1)) {
			if (toCheckOther) {
				currStatus = checkWinning();
				break;
			} else {
				toCheckOther = true;
			}
		//If he chose something, then it will be put
		} else if (toCheckOther) {
			toCheckOther = false;
			put(move, Board::O);
		} else {
			put(move, Board::O);
		}
	}
	//Checking if the game is over
	if (currStatus == XWins) {
		cout << "X player won!" << endl;
	} else if (currStatus == OWins) {
		cout << "O player won!" << endl;
	} else {
		cout << "It's a tie!" << endl;
	}
}

/***************************************
 * Function Name: calcMoves
 * The Input: the type of the player
 * The Output: his options
 * The Function Operation: checking all
 *  of the adv' Cells and finding a spot
 *  that will turn some of them
 **************************************/
vector<Point> *Game::calcMoves(Board::Cell cell) {
	//Creating the new vector
	vector<Point> *options = new vector<Point>();
	//Keeping a pointer to the adv' locations
	vector<Point> *advLocations;
	switch (cell) {
		case Board::X: advLocations = oLocations;
							 break;
		case Board::O: advLocations = xLocations;
							 break;
		default: //Shouldn't happen
				 break;
	}
	//Saving the directions as an array to go through them easily
	Direction dirs[8] = {Up, Down, Left, Right, UpLeft, UpRight, DownLeft, DownRight};
	//For every adv location
	for (vector<Point>::iterator it = advLocations->begin(); it != advLocations->end(); it++) {
		//Checking all of the directions
		for (int indexer = 0; indexer < 8; indexer++) {
			//Getting the point for the curr direction
			Point currPoint = getPointFromDir(*it, dirs[indexer]);
			//Checking if there is a move in this direction
			if (checkMoveEmpty(cell, currPoint, dirs[indexer])) {
				currPoint++;//.deAlignToPrint();
				if (!isPointInVector(options, currPoint)) {
					options->push_back(currPoint);
				}
			}
		}
	}
	return options;
}

/***************************************
 * Function Name: checkMoveEmpty
 * The Input: the player's type,
 *            the first location in the
 *             direction,
 *            the direction
 * The Output: true - there is a move here
 *             false - there isn't
 * The Function Operation: checking
 *  if the curr location is empty and
 *  if it is, then it will check the
 *  other Cells in this direction
 **************************************/
bool Game::checkMoveEmpty(Board::Cell cell, Point point, Direction dir) {
	if (!gameBoard->pointExists(point)) {
		/*
		 * If the point is not on the board,
		 * then obviously it's not empty
		 */
		return false;
	}
	Board::Cell currCell = gameBoard->getCell(point);
	if (currCell == Board::Empty) {
		/*
		 * It is empty, so we'll reverse the direction
		 * so we could see if it really would turn
		 * some Cells
		 */
		reverseDir(&dir);
		return checkMove(cell, getPointFromDir(point, dir), dir);
	} else {
		return false;
	}
}

/***************************************
 * Function Name: checkMove
 * The Input: the player's type,
 *            the curr location in the
 *             direction,
 *            the direction
 * The Output: true - there is a move here
 *             false - there isn't
 * The Function Operation: checking if
 *  there is a series of
 *  X,O,...,O,X and vice versa
 **************************************/
bool Game::checkMove(Board::Cell playerType, Point point, Direction dir) {
	if (!gameBoard->pointExists(point)) {
		/*
		 * If the point is not on the board,
		 * then obviously it's not empty
		 */
		return false;
	}
	Board::Cell currCell = gameBoard->getCell(point);
	if (currCell == playerType) {
		return true;
	} else if (currCell == Board::Empty) {
		return false;
	} else {
		//Recursively checking the next points in the series
		return checkMove(playerType, getPointFromDir(point, dir), dir);
	}
}

/***************************************
 * Function Name: put
 * The Input: the point to select,
 *            the type of the player
 * The Output: true - the operation
 *                    was successful
 *             false - otherwise
 * The Function Operation: going
 *  through the series, and noting which
 *  Cells to turn
 **************************************/
bool Game::put(Point point, Board::Cell cell) {
	if (!gameBoard->pointExists(point)) {
		/*
		 * If the point is not on the board,
		 * then obviously it's not empty
		 */
		return false;
	} else {
		/*
		 * Going through all of the directions
		 * and saving a list of Cells to turn
		 */
		Direction dirs[8] = {Up, Down, Left, Right, UpLeft, UpRight, DownLeft, DownRight};
		for (int indexer = 0; indexer < 8; indexer++) {
			vector<Point> *tempLocations = new vector<Point>();
			if (!isPointInVector(tempLocations, point)) {
				tempLocations->push_back(point);
			}
			if (tryToPut(cell, getPointFromDir(point, dirs[indexer]), dirs[indexer], tempLocations)) {
				for (vector<Point>::iterator it = tempLocations->begin(); it != tempLocations->end(); ++it) {
					gameBoard->put(*it, cell);
					removePointFromVector(xLocations, *it);
					removePointFromVector(oLocations, *it);
					switch (cell) {
						case Board::X: xLocations->push_back(*it);
									   break;
						case Board::O: oLocations->push_back(*it);
									   break;
						default: //Shouldn't happen
								 break;
					}
				}
			}
			delete tempLocations;
		}
	}
	return true;
}

/***************************************
 * Function Name: tryToPut
 * The Input: the point to select,
 *            the type of the player,
 *            the vector of Cells to turn
 * The Output: true - the operation
 *                    was successful
 *             false - otherwise
 * The Function Operation: going
 *  through the series, and noting which
 *  Cells to turn (Recursive sub-method)
 **************************************/
bool Game::tryToPut(Board::Cell cell, Point point, Direction dir, vector<Point> *tempLocations) {
	if (!gameBoard->pointExists(point)) {
		/*
		 * If the point is not on the board,
		 * then obviously it's not empty
		 */
		return false;
	} else {
		Board::Cell currCell = gameBoard->getCell(point);
		if (currCell == cell) {
			return true;
		} else if (currCell == Board::Empty) {
			return false;
		} else {
			//Adding the Cells to turn
			if (!isPointInVector(tempLocations, point)) {
				tempLocations->push_back(point);
			}
			return tryToPut(cell, getPointFromDir(point, dir), dir, tempLocations);
		}
	}
}

/***************************************
 * Function Name: printBoard
 * The Input: no input
 * The Output: printing the board to cout
 * The Function Operation: using
 * 	board->print()
 **************************************/
void Game::printBoard() const {
	gameBoard->printBoard();
}

/***************************************
 * Function Name: checkWinning
 * The Input: no input
 * The Output: the next GameStatus
 * The Function Operation: if there are
 *  no more moves left, checking the
 *  number of Cells each player has on
 *  the board, and announcing the winner
 **************************************/
Game::GameStatus Game::checkWinning() const {
	if (xLocations->size() > oLocations->size()) {
		return XWins;
	} else if (xLocations->size() < oLocations->size()) {
		return OWins;
	} else {
		return Tie;
	}
}
