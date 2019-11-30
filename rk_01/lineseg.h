#ifndef LINESEG_H
#define LINESEG_H

#include <cmath>

#include "point.h"

class LineSeg
{
public:
	LineSeg(int sx, int sy, int px, int py) : p1(sx, sy), p2(px, py) {}
	LineSeg(Point s, Point p) : p1(s), p2(p) {}
	
	Point& getP1() { return p1; }
	Point& getP2() { return p2; }
	
	void setP1(const Point &value) { p1 = value; }
	void setP2(const Point &value) { p2 = value; }
	
	bool isHorizontal() { return p1.y() == p2.y(); }
	bool isVertical() { return p1.x() == p2.x(); }
	
	void swapPoints();
	Point getParam(double t);
	
private:
	Point p1, p2;
};

#endif // LINESEG_H
