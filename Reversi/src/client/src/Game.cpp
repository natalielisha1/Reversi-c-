/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex3
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

Game::Game(char xPlayerIdentifier, char oPlayerIdentifier) {
	xLocations = new vector<Point>();
	oLocations = new vector<Point>();

	gameBoard = new Board(xLocations, oLocations);

	switch (xPlayerIdentifier) {
		case HUMAN_PLAYER_IDENTIFIER: xPlayer = new HumanPlayer(Board::X);
									  break;
		case COMP_PLAYER_IDENTIFIER:  xPlayer = new CompPlayer(Board::X);
									  break;
		case BLANK_PLAYER_IDENTIFIER: xPlayer = new BlankPlayer(Board::X);
									  break;
		case REMOTE_PLAYER_IDENTIFIER:xPlayer = new RemotePlayer(Board::X);
									  break;
		default:                      xPlayer = new HumanPlayer(Board::X);
									  break;
	}
	switch (oPlayerIdentifier) {
		case HUMAN_PLAYER_IDENTIFIER: oPlayer = new HumanPlayer(Board::O);
									  break;
		case COMP_PLAYER_IDENTIFIER:  oPlayer = new CompPlayer(Board::O);
									  break;
		case BLANK_PLAYER_IDENTIFIER: oPlayer = new BlankPlayer(Board::O);
									  break;
		case REMOTE_PLAYER_IDENTIFIER:oPlayer = new RemotePlayer(Board::O);
									  break;
		default:                      oPlayer = new HumanPlayer(Board::O);
									  break;
	}

	if (xPlayerIdentifier == REMOTE_PLAYER_IDENTIFIER) {
		if (xPlayer->getType() == Board::O) {
			Player *temp = xPlayer;
			xPlayer = oPlayer;
			xPlayer->setType(Board::X);
			oPlayer = temp;
		}
	}
	if (oPlayerIdentifier == REMOTE_PLAYER_IDENTIFIER) {
		if (oPlayer->getType() == Board::X) {
			Player *temp = oPlayer;
			oPlayer = xPlayer;
			oPlayer->setType(Board::O);
			xPlayer = temp;
		}
	}

	currStatus = NotPlaying;
}

Game::Game(const Game& other) {
	xLocations = new vector<Point>(*other.xLocations);
	oLocations = new vector<Point>(*other.oLocations);
	xPlayer = new BlankPlayer(Board::X);
	oPlayer = new BlankPlayer(Board::O);

	gameBoard = new Board(*other.gameBoard);

	currStatus = other.currStatus;
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
		xPlayer->sendMessage("Current board:");
		xPlayer->sendMessage("");
		string *boardToString = gameBoard->boardToString();
		xPlayer->sendMessage(boardToString->c_str());
		delete boardToString;
		if (move != Point(-1,-1)) {
			++move;//.deAlignToPrint();
			string tempString = string("O played ");
			string *pointToString = move.pointToString();
			tempString.append(pointToString->c_str());
			delete pointToString;
			xPlayer->sendMessage(tempString.c_str());
			xPlayer->sendMessage("");
		}
		xPlayer->sendMessage("X: It's your move");
		//Calc'ing the moves available to X
		tempOptions = calcMoves(Board::X);
		Point bestMove = getBestMove(tempOptions, Board::X);
		//Letting him choose
		move = xPlayer->makeMove(tempOptions, bestMove);
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
		oPlayer->sendMessage("Current board:");
		oPlayer->sendMessage("");
		boardToString = gameBoard->boardToString();
		oPlayer->sendMessage(boardToString->c_str());
		delete boardToString;
		if (move != Point(-1,-1)) {
			++move;//.deAlignToPrint();
			string tempString = string("X played ");
			string *pointToString = move.pointToString();
			tempString.append(pointToString->c_str());
			delete pointToString;
			oPlayer->sendMessage(tempString.c_str());
			oPlayer->sendMessage("");
		}
		oPlayer->sendMessage("O: It's your move");
		//Calc'ing the moves available to O
		tempOptions = calcMoves(Board::O);
		bestMove = getBestMove(tempOptions, Board::O);
		//Letting him choose
		move = oPlayer->makeMove(tempOptions, bestMove);
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
		xPlayer->sendMessage("X player won!");
		oPlayer->sendMessage("X player won!");
	} else if (currStatus == OWins) {
		xPlayer->sendMessage("O player won!");
		oPlayer->sendMessage("O player won!");
	} else {
		xPlayer->sendMessage("It's a tie!");
		oPlayer->sendMessage("It's a tie!");
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
				++currPoint;//.deAlignToPrint();
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

/***************************************
 * Function Name: rankOptions
 * The Input: vector of Points (options)
 * and a type of cell
 * The Output: a map of rank according
 * to a specific point and that same point
 * The Function Operation: the function makes
 * a list of the rank that defines
 * every possible move the current player has
 **************************************/
map<int, Point> Game::rankOptions(vector<Point>* options, Board::Cell cell) {
	map<int, Point> theMap = map<int, Point>();
	vector<Point> *currLocations;
	vector<Point> *advLocations;
	Board::Cell adv;
	if (cell == Board::X) {
		adv = Board::O;
	} else if (cell == Board::O) {
		adv = Board::X;
	}
	if (options->size() == 0) {
		return theMap;
	}
	for (vector<Point>::iterator it1 = options->begin(); it1 != options->end(); ++it1) {
		Game imaginaryGame = Game(*this);
		imaginaryGame.put(*it1, cell);
		vector<Point> *advOptions = imaginaryGame.calcMoves(adv);
		for (vector<Point>::iterator it = advOptions->begin(); it != advOptions->end(); ++it) {
			--(*it);
		}
		if (advOptions->size() == 0) {
			theMap[INT_MIN] = *it1;
			delete advOptions;
			continue;
		}
		int maxDiff = INT_MIN;
		for (vector<Point>::iterator it2 = advOptions->begin(); it2 != advOptions->end(); ++it2) {
			if (*it2 == Point(-1,-1)) {
				continue;
			}
			Game inceptionGame = Game(*this);
			inceptionGame.put(*it1, cell);
			inceptionGame.put(*it2, adv);
			switch (cell) {
				case Board::X:  currLocations = inceptionGame.xLocations;
								advLocations = inceptionGame.oLocations;
								break;
				case Board::O:  currLocations = inceptionGame.oLocations;
								advLocations = inceptionGame.xLocations;
								break;
				default:		return theMap;
			}

			int diff = advLocations->size() - currLocations->size();
			if (diff > maxDiff) {
				maxDiff = diff;
			}
		}
		theMap[maxDiff] = *it1;
		delete advOptions;
	}
	return theMap;
}

/***************************************
 * Function Name: getBestMove
 * The Input: a vector of point (options) and
 * a cell.
 * The Output: a point
 * The Function Operation: the function returns
 * a point which represents the best move the
 * current player can do
 **************************************/
Point Game::getBestMove(vector<Point>* options, Board::Cell cell) {
	vector<Point>* optionsCopy = new vector<Point>(*options);
	for (vector<Point>::iterator it = optionsCopy->begin(); it != optionsCopy->end(); ++it) {
		--(*it);
	}
	map<int, Point> rankedOptions = rankOptions(optionsCopy, cell);
	delete optionsCopy;
	Point bestMove = Point(-1,-1);
	if (!rankedOptions.empty()) {
		bestMove = (*rankedOptions.begin()).second;
	}
	return bestMove;
}

Board*& Game::getGameBoard() {
	return gameBoard;
}

Game::GameStatus Game::getCurrentStatus() {
	return this->currStatus;
}

void Game::setCurrentStatus(Game::GameStatus status) {
	currStatus = status;
}

Player*& Game::getOPlayer() {
	return oPlayer;
}

Player*& Game::getXPlayer() {
	return xPlayer;
}

