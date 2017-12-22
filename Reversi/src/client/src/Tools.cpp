/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex4
 **************************************/

#include "Tools.h"
using namespace std;

/***************************************
 * Function Name: pointFromDir
 * The Input: the point, a direction
 * The Output: the new point
 * The Function Operation: returning the
 *  next point in the selected direction
 **************************************/
Point getPointFromDir(Point point, Direction dir) {
	switch (dir) {
		case Up: return Point(point.getX() - 1, point.getY());
		case Down: return Point(point.getX() + 1, point.getY());
		case Right: return Point(point.getX(), point.getY() + 1);
		case Left: return Point(point.getX(), point.getY() - 1);
		case DownLeft: return Point(point.getX() + 1, point.getY() - 1);
		case DownRight: return Point(point.getX() + 1, point.getY() + 1);
		case UpLeft: return Point(point.getX() - 1, point.getY() - 1);
		case UpRight: return Point(point.getX() - 1, point.getY() + 1);
	}
	return Point(-1, -1);
}

/***************************************
 * Function Name: reverseDir
 * The Input: the dir to turn
 * The Output: no output
 * The Function Operation: turning the
 *  direction to the exact opposite
 **************************************/
void reverseDir(Direction *dir) {
	switch (*dir) {
		case Up:    *dir = Down;
					break;
		case Down:  *dir = Up;
					break;
		case Right: *dir = Left;
					break;
		case Left:  *dir = Right;
					break;
		case DownLeft:  *dir = UpRight;
						break;
		case DownRight: *dir = UpLeft;
						break;
		case UpLeft: 	*dir = DownRight;
						break;
		case UpRight: 	*dir = DownLeft;
						break;
	}
}

/***************************************
 * Function Name: vectorContains
 * The Input: the vector to check,
 *            a point to search
 * The Output: true - the point is in
 *                    the vector
 *             false - otherwise
 * The Function Operation: going through
 *  the vector and comparing the points
 **************************************/
bool isPointInVector(vector<Point> *theVector, Point object) {
	for (vector<Point>::iterator it = theVector->begin(); it != theVector->end(); ++it) {
		if (*it == object) {
			return true;
		}
	}
	return false;
}

/***************************************
 * Function Name: vectorRemove
 * The Input: the vector to check,
 *            a point to search
 * The Output: true - the point is in
 *                    the vector and was
 *                    removed from it
 *             false - otherwise
 * The Function Operation: going through
 *  the vector and comparing the points,
 *  and if found, removing the point from
 *  the vector
 */
bool removePointFromVector(vector<Point> *theVector, Point object) {
	for (vector<Point>::iterator it = theVector->begin(); it != theVector->end(); ++it) {
		if (*it == object) {
			theVector->erase(it);
			return true;
		}
	}
	return false;
}
