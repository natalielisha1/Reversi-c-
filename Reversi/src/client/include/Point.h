/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex3
 **************************************/

#ifndef POINT_H_
#define POINT_H_

#include <iostream>
#include <string>
#include <string.h>
#include "ToolsForStrings.h"

class Point {
public:
	Point();
	Point(int x, int y);
	int getX() const;
	int getY() const;
	void setX(int x);
	void setY(int y);
	void printPoint() const;
	std::string *pointToString() const;
	bool operator==(const Point& p);
	bool operator!=(const Point& p);
	void operator--(); //void alignToPrint();
	void operator++(); //void deAlignToPrint();
private:
	int xLoc;
	int yLoc;
};

#endif /* INCLUDE_POINT_H_ */
