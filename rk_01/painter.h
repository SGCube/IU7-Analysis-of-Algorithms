#ifndef PAINTER_H
#define PAINTER_H

#include <QPainter>
#include "point.h"

class Painter : public QPainter
{
public:
	Painter();
	void setColorLine(QColor color) { colorLine = color; }
	void setColorBg(QColor color) { colorBg = color; }
	void drawLineSeg(int x1, int y1, int x2, int y2);
	void drawBrokenLine(std::vector<Point> &points);
	QColor getColorLine() const { return colorLine; }
	QColor getColorBg() const { return colorBg; }
	
private:
	QPen pen;
	QColor colorLine;
	QColor colorBg;
	void setLine();
};

#endif // PAINTER_H
