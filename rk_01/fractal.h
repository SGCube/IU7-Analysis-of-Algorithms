#ifndef FRACTAL_H
#define FRACTAL_H

#include <vector>
#include "point.h"

std::vector<Point> get_dragon_fractal(Point p1, Point p2, int n);

std::vector<Point> get_dragon_fractal_rec(std::vector<Point> line, int n);

#endif // FRACTAL_H
