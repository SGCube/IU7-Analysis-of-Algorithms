#include "lineseg.h"

void LineSeg::swapPoints()
{
	Point tmp = p1;
	p1 = p2;
	p2 = tmp;
}

Point LineSeg::getParam(double t)
{
	int x = p1.x() + round((p2.x() - p1.x()) * t);
	int y = p1.y() + round((p2.y() - p1.y()) * t);
	return Point(x, y);
}
