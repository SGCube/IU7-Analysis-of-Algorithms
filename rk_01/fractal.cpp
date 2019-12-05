#include "fractal.h"

#include <QtMath>

void rotate_line(std::vector<Point> &line, Point &pc)
{
	double x, y;
	double xc = pc.x(), yc = pc.y();
	for (auto p : line)
	{
		x = p.x();
		y = p.y();
		p.setX(xc + (y - yc));
		p.setY(yc - (x - xc));
	}
}

std::vector<Point> get_dragon_fractal(Point p1, Point p2, int n)
{
	std::vector<Point> line;
	line.push_back(p1);
	line.push_back(p2);
	
	for (int i = 0; i < n; i++)
	{
		int xc = line.back().x(), yc = line.back().y();
		int old_size = line.size();
		for (int j = old_size - 2; j >= 0; j--)
		{
			int xx = xc + (line[j].y() - yc);
			int yy = yc - (line[j].x() - xc);
			line.push_back(Point(xx, yy));
		}
	}
	
	return line;
}

std::vector<Point> get_dragon_fractal_rec(std::vector<Point> line, int n)
{
	if (n == 0)
		return line;
	
	std::vector<Point> new_line = get_dragon_fractal_rec(line, n - 1);
	
	int xc = new_line.back().x(), yc = new_line.back().y();
	int old_size = new_line.size();
	for (int j = old_size - 2; j >= 0; j--)
	{
		int xx = xc + (new_line[j].y() - yc);
		int yy = yc - (new_line[j].x() - xc);
		new_line.push_back(Point(xx, yy));
	}
	
	for (auto p : new_line)
		line.push_back(p);
	return line;
}
