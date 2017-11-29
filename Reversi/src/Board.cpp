/***************************************
 * Student Name: Ofek Segal
 * Student ID: 315638288
 * Exercise Name: Ex2
 **************************************/

#include "Board.h"
using namespace std;

/***************************************
 * Function Name: Board (Constructor)
 * The Input: the size of the board
 * The Output: the empty board
 * The Function Operation: initializing
 *  the board
 **************************************/
Board::Board(int xSize, int ySize) {
	theOuterSize = xSize;
	theInnerSize = ySize;
	//Memory Initialization
	theBoard = new Cell *[theOuterSize];
	for (int indexer = 0; indexer < theOuterSize; indexer++) {
		theBoard[indexer] = new Cell[theInnerSize];
	}
	//Making sure that it will a clean board
	for (int outer = 0; outer < theOuterSize; outer++) {
		for (int inner = 0; inner < theInnerSize; inner++) {
			theBoard[outer][inner] = Empty;
		}
	}
	//Adding the start positions
	int middleOuter = theOuterSize/2 - 1;
	int middleInner = theInnerSize/2 - 1;
	theBoard[middleOuter][middleInner] = O;
	theBoard[middleOuter + 1][middleInner + 1] = O;
	theBoard[middleOuter][middleInner + 1] = X;
	theBoard[middleOuter + 1][middleInner] = X;
	quantity = 4;

}

/***************************************
 * Function Name: Board (Constructor)
 * The Input: the size of the board,
 *            the vectors that maintain
 *            the list of Cells on the
 *            board
 * The Output: the empty board
 * The Function Operation: initializing
 *  the board, and saving the Cell
 *  locations
 **************************************/
Board::Board(vector<Point> *xLocations, vector<Point> *oLocations, int xSize,
		int ySize): theOuterSize(xSize), theInnerSize(ySize) {
	//Memory Initialization
	theBoard = new Cell *[theOuterSize];
	for (int indexer = 0; indexer < theOuterSize; indexer++) {
		theBoard[indexer] = new Cell[theInnerSize];
	}
	//Making sure that it will a clean board
	for (int outer = 0; outer < theOuterSize; outer++) {
		for (int inner = 0; inner < theInnerSize; inner++) {
			theBoard[outer][inner] = Empty;
		}
	}
	//Adding the start positions
	int middleOuter = theOuterSize/2 - 1;
	int middleInner = theInnerSize/2 - 1;
	theBoard[middleOuter][middleInner] = O;
	theBoard[middleOuter + 1][middleInner + 1] = O;
	theBoard[middleOuter][middleInner + 1] = X;
	theBoard[middleOuter + 1][middleInner] = X;
	quantity = 4;
	if (!isPointInVector(xLocations, Point(middleOuter, middleInner + 1))) {
		xLocations->push_back(Point(middleOuter, middleInner + 1));
	}
	if (!isPointInVector(xLocations, Point(middleOuter + 1, middleInner))) {
		xLocations->push_back(Point(middleOuter + 1, middleInner));
	}
	if (!isPointInVector(oLocations, Point(middleOuter, middleInner))) {
		oLocations->push_back(Point(middleOuter, middleInner));
	}
	if (!isPointInVector(oLocations, Point(middleOuter + 1, middleInner + 1))) {
		oLocations->push_back(Point(middleOuter + 1, middleInner + 1));
	}
}

Board::Board(const Board& other) {
	quantity = other.quantity;
	theOuterSize = other.theOuterSize;
	theInnerSize = other.theInnerSize;

	//Memory Initialization
	theBoard = new Cell *[theOuterSize];
	for (int indexer = 0; indexer < theOuterSize; indexer++) {
		theBoard[indexer] = new Cell[theInnerSize];
	}

	for (int outer = 0; outer < theOuterSize; outer++) {
		for (int inner = 0; inner < theInnerSize; inner++) {
			theBoard[outer][inner] = other.theBoard[outer][inner];
		}
	}
}

/***************************************
 * Function Name: ~Board (Destructor)
 * The Input: no input
 * The Output: no output
 * The Function Operation: freeing
 *  memory
 **************************************/
Board::~Board() {
	//Going through the 2D array and freeing it
	for (int indexer = 0; indexer < theOuterSize; indexer++) {
		delete [] theBoard[indexer];
	}
	delete [] theBoard;
}

/***************************************
 * Function Name: print
 * The Input: no input
 * The Output: the board in cout
 * The Function Operation: going through
 *  the board and printing its lines
 **************************************/
void Board::printBoard() const {
	cout << " | ";
	for (int counter = 0; counter < theInnerSize; counter++) {
		cout << (counter + 1) << " | ";
	}
	cout << endl;
	cout << string(2 + 4 * theInnerSize, '-') << endl;
    //Going through the board, line by line
    for (int outer = 0; outer < theOuterSize; outer++) {
    	cout << (outer + 1) << "| ";
		for (int inner = 0; inner < theInnerSize; inner++) {
			//Choosing what to print
			switch (theBoard[outer][inner]) {
				case Empty: cout << " "; break;
				case X: cout << "X"; break;
				case O: cout << "O"; break;
			}
			cout << " | ";
		}
		cout << endl;
		cout << string(2 + 4 * theInnerSize, '-') << endl;
    }
}

/***************************************
 * Function Name: boardToString
 * The Input: no input
 * The Output: the board to string
 * The Function Operation: going through
 *  the board and appending its lines
 *  to the return variable
 **************************************/
string *Board::boardToString() const {
	string *toReturn = new string();
	toReturn->append(" | ");
	for (int counter = 0; counter < theInnerSize; counter++) {
		toReturn->append(myToString(counter + 1));
		toReturn->append(" | ");
	}
	toReturn->append("\n");
	toReturn->append(string(2 + 4 * theInnerSize, '-'));
	toReturn->append("\n");
    //Going through the board, line by line
    for (int outer = 0; outer < theOuterSize; outer++) {
    	toReturn->append(myToString(outer + 1));
    	toReturn->append("| ");
		for (int inner = 0; inner < theInnerSize; inner++) {
			//Choosing what to print
			switch (theBoard[outer][inner]) {
				case Empty: toReturn->append(" "); break;
				case X: toReturn->append("X"); break;
				case O: toReturn->append("O"); break;
			}
			toReturn->append(" | ");
		}
		toReturn->append("\n");
		toReturn->append(string(2 + 4 * theInnerSize, '-'));
		toReturn->append("\n");
    }
    return toReturn;
}

/***************************************
 * Function Name: pointExists
 * The Input: a point
 * The Output: if the point is in
 *  the board
 * The Function Operation: checking if
 *  the point fits in the board's
 *  borders
 **************************************/
bool Board::pointExists(Point point) {
	return 0 <= point.getX() &&
		   point.getX() < theOuterSize &&
		   0 <= point.getY() &&
		   point.getY() < theInnerSize;
}

/***************************************
 * Function Name: getCell
 * The Input: a point
 * The Output: the Cell in the point's
 *  location in the board
 * The Function Operation: returning
 *  the 2D arr value in the point's
 *  location
 **************************************/
Board::Cell Board::getCell(Point point) {
	return theBoard[point.getX()][point.getY()];
}

/***************************************
 * Function Name: put
 * The Input: a point
 *            the type of cell to insert
 * The Output: true - the operation was
 *                    successful
 *             false - otherwise
 * The Function Operation: checking if
 *  the point exists, and if so,
 *  replacing the cell in that location
 *  with playerType
 **************************************/
bool Board::put(Point point, Cell playerType) {
	if (!pointExists(point)) {
		return false;
	} else {
		theBoard[point.getX()][point.getY()] = playerType;
		return true;
	}
}

/***************************************
 * Function Name: isCellInPointEmpty
 * The Input: a point
 * The Output: true or false
 * The Function Operation: the function
 * returns true if the current cell in
 * the given point is empty and false
 * otherwise.
 **************************************/
bool Board::isCellInPointEmpty(Point p) {
	if (!this->pointExists(p)) {
		return false;
	}	else if(theBoard[p.getX()][p.getY()] == Empty) {
		return true;
	} else {
		return false;
	}
}

/***************************************
 * Function Name: getQuantity
 * The Input: no input
 * The Output: an integer
 * The Function Operation: the function
 * returns the current quantity of full
 * cells on the board.
 **************************************/
int Board::getQuantity() {
	return quantity;
}

//Outsider functions
/***************************************
 * Function Name: advCellType
 * The Input: a cell
 * The Output: the adversary's cell
 * The Function Operation: the function
 * returns the adversary's cell
 **************************************/
Board::Cell advCellType(Board::Cell cell) {
	switch (cell) {
		case Board::X: return Board::O;
		case Board::O: return Board::X;
		default: return Board::Empty;
	}
}
