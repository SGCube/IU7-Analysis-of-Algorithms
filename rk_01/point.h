#ifndef POINT_H
#define POINT_H

class Point
{
public:
	Point(int x, int y);
	
	int x();
	int y();
	void setX(int x);
	void setY(int y);
	
	bool operator==(const Point &p);
	
private:
	int xcoord;
	int ycoord;
};

double dist(Point p1, Point p2);

#endif // POINT_H
