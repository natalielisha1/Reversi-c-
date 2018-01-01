/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex5
 **************************************/

#ifndef BOARD_H_
#define BOARD_H_

#include <iostream>
#include <vector>
#include <string>
#include <string.h>

#include "Point.h"
#include "Tools.h"

#define X_SIZE 8
#define Y_SIZE 8

class Board {
public:
	//Defining what is a "Cell"
	enum Cell { Empty, X, O };

	Board(int xSize = X_SIZE, int ySize = Y_SIZE);
	Board(std::vector<Point> *xLocations, std::vector<Point> *oLocations, int xSize = X_SIZE, int ySize = Y_SIZE);
	Board(const Board& other);
	~Board();

	void printBoard() const;
	std::string *boardToString() const;

	bool isCellInPointEmpty(Point p);
	bool pointExists(Point point);

	Cell getCell(Point point);

	bool put(Point point, Cell playerType);
	void putClean(Point point, Cell playerType);

	int getQuantity();
private:
	Cell** theBoard;
	int theOuterSize;
	int theInnerSize;
	int quantity;

};

Board::Cell advCellType(Board::Cell cell);

#endif /* BOARD_H_ */
