/***************************************
 * Student Name: Ofek Segal
 * Student ID: 315638288
 * Exercise Name: Ex2
 **************************************/

#ifndef TOOLS_H_
#define TOOLS_H_

#include <vector>
#include <string>
#include <iostream>
#include "Point.h"

enum Direction { Up, Down, Left, Right, UpLeft, UpRight, DownLeft, DownRight};

Point getPointFromDir(Point point, Direction dir);
void reverseDir(Direction *dir);

bool isPointInVector(std::vector<Point> *theVector, Point object);
bool removePointFromVector(std::vector<Point> *theVector, Point object);

#endif /* TOOLS_H_ */
