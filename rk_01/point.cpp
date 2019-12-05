#include "point.h"

#include <math.h>

Point::Point(int x, int y)
{
	xcoord = x;
	ycoord = y;
}

int Point::x()
{
	return xcoord;
}

int Point::y()
{
	return ycoord;
}

void Point::setX(int x)
{
	xcoord = x;
}

void Point::setY(int y)
{
	ycoord = y;
}

bool Point::operator==(const Point &p)
{
	return ((xcoord == p.xcoord) && (ycoord == p.ycoord));
}
