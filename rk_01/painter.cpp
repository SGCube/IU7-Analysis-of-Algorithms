#include "painter.h"

Painter::Painter() :
	QPainter(),
	pen(QColor(0, 0, 0)),
	colorLine(0, 0, 0),
	colorBg(255, 255, 255)
{
	
}

void Painter::drawLineSeg(int x1, int y1, int x2, int y2)
{
	setLine();
	drawLine(x1, y1, x2, y2);
}

void Painter::drawBrokenLine(std::vector<Point> &points)
{
	setLine();
	for (unsigned i = 1; i < points.size(); i++)
	{
		drawLine(points[i - 1].x(), points[i - 1].y(),
				points[i].x(), points[i].y());
	}
}

void Painter::setLine()
{
	pen.setColor(colorLine);
	pen.setWidth(1);
	setPen(pen);
}
