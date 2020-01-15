#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <vector>

#include "painter.h"
#include "point.h"

class Canvas : public QWidget
{
	Q_OBJECT
	
public:
	explicit Canvas(QWidget *parent = nullptr);
	void setCanvas(QImage* image, Painter* p);
	
protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	
private:
	QImage* img;
	Painter* painter;
	
	Point startPoint;
	
signals:
	void setStart(Point p);

};

#endif // CANVAS_H
