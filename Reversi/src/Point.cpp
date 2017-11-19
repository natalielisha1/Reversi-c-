/***************************************
 * Student Name: Ofek Segal
 * Student ID: 315638288
 * Exercise Name: Ex2
 **************************************/

#include "Point.h"
using namespace std;

/***************************************
 * Function Name: Point (Constructor)
 * The Input: no input
 * The Output: the new point
 * The Function Operation: setting
 *  coordinates
 **************************************/
Point::Point(int x, int y):xLoc(x), yLoc(y) {}

/***************************************
 * Function Name: getX
 * The Input: no input
 * The Output: the xCords
 * The Function Operation: returning the
 *  var
 **************************************/
int Point::getX() const {
	return xLoc;
}

/***************************************
 * Function Name: getY
 * The Input: no input
 * The Output: the yCords
 * The Function Operation: returning the
 *  var
 **************************************/
int Point::getY() const {
	return yLoc;
}

/***************************************
 * Function Name: setX
 * The Input: the new xCords
 * The Output: no output
 * The Function Operation: setting the
 *  var
 **************************************/
void Point::setX(int x) {
	xLoc = x;
}

/***************************************
 * Function Name: setY
 * The Input: the new yCords
 * The Output: no output
 * The Function Operation: setting the
 *  var
 **************************************/
void Point::setY(int y) {
	yLoc = y;
}

/***************************************
 * Function Name: printPoint
 * The Input: no input
 * The Output: printing the point to cout
 * The Function Operation: printing
 *  to cout
 **************************************/
void Point::printPoint() const {
	cout << "(";
	cout << xLoc;
	cout << ",";
	cout << yLoc;
	cout << ")";
}

/***************************************
 * Function Name: pointToString
 * The Input: no input
 * The Output: the point as a string
 * The Function Operation: creating a
 *  new string and appending the point
 *  values to it
 **************************************/
string *Point::pointToString() const {
	string *toReturn = new string("(");
	toReturn->append(myToString(xLoc));
	toReturn->append(",");
	toReturn->append(myToString(yLoc));
	toReturn->append(")");
	return toReturn;
}

/***************************************
 * Function Name: operator==
 * The Input: the second point
 * The Output: true - the points are
 *                    equal
 *             false - otherwise
 * The Function Operation: checking
 *  their x and y cords
 **************************************/
bool Point::operator==(const Point& p) {
	return this->xLoc == p.xLoc && this->yLoc == p.yLoc;
}

/***************************************
 * Function Name: operator!=
 * The Input: the second point
 * The Output: true - the points are
 *                    not equal
 *             false - otherwise
 * The Function Operation: checking
 *  their x and y cords
 **************************************/
bool Point::operator!=(const Point& p) {
	return !(this->xLoc == p.xLoc && this->yLoc == p.yLoc);
}

/***************************************
 * Function Name: alignToPrint
 * The Input: no input
 * The Output: no output
 * The Function Operation: changing the
 *  point's range to 0-7 (from 1-8)
 **************************************/
void Point::operator--() { //void Point::alignToPrint() {
	xLoc--;
	yLoc--;
}

/***************************************
 * Function Name: deAlignToPrint
 * The Input: no input
 * The Output: no output
 * The Function Operation: changing the
 *  point's range to 1-8 (from 0-7)
 **************************************/
void Point::operator++() { //void Point::deAlignToPrint() {
	xLoc++;
	yLoc++;
}
