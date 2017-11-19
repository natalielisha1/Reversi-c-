/***************************************
 * Student Name: Ofek Segal
 * Student ID: 315638288
 * Exercise Name: Ex2
 **************************************/

#ifndef BOARD_H_
#define BOARD_H_

#include <iostream>
#include <vector>
#include <string>
#include "Point.h"
#include "Tools.h"

class Board {
public:
	//Defining what is a "Cell"
	enum Cell { Empty, X, O };
	Board(int xSize = 8, int ySize = 8);
	Board(std::vector<Point> *xLocations, std::vector<Point> *oLocations, int xSize = 8, int ySize = 8);
	~Board();
	void printBoard() const;
	bool isCellInPointEmpty(Point p);
	std::string *boardToString() const;
	bool pointExists(Point point);
	Cell getCell(Point point);
	bool put(Point point, Cell playerType);
	int getQuantity();
private:
	Cell** theBoard;
	int theOuterSize;
	int theInnerSize;
	int quantity;

};

Board::Cell advCellType(Board::Cell cell);

#endif /* BOARD_H_ */
