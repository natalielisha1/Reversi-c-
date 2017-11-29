/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex3
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
