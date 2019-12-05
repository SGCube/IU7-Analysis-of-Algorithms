#include "vector.h"

double Vector::scalarMultiply(const Vector& a, const Vector& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector Vector::vectorMultiply(const Vector& a, const Vector& b)
{
	return Vector(a.y * b.z - a.z * b.y,
				  a.z * b.x - a.x * b.z,
				  a.x * b.y - a.y * b.x);
}

Vector Vector::normal(Vector &v, int dir)
{
	if (dir == 1)
		return Vector(-v.y, v.x);
	return Vector(v.y, -v.x);
}
