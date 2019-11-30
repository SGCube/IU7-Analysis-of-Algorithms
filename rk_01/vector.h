#ifndef VECTOR_H
#define VECTOR_H

#include "point.h"

struct Vector
{
    int x;
    int y;
    int z;
	
	Vector() {}
	
    Vector(int x_, int y_, int z_ = 0) : x(x_), y(y_), z(z_) {}
	
    Vector(Point p2, Point p1) :
		x(p2.x() - p1.x()), y(p2.y() - p1.y()), z(0) {};
	
	static double scalarMultiply(const Vector& a, const Vector& b);
	
	static Vector vectorMultiply(const Vector& a, const Vector& b);
	
	static Vector normal(Vector &v, int dir);
};

#endif // VECTOR_H
