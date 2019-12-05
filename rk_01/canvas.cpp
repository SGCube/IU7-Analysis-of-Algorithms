#include <QDebug>

#include "canvas.h"

Canvas::Canvas(QWidget *parent) :
	QWidget(parent),
	img(nullptr),
	painter(nullptr),
	startPoint(0, 0)
{
	setMouseTracking(true);
}

void Canvas::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);
	painter->begin(this);
	painter->drawImage(0, 0, *img);
	painter->end();
}

void Canvas::setCanvas(QImage *image, Painter *p)
{
	img = image;
	painter = p;
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
	if (event->button() != Qt::LeftButton)
		return;
	
	int x = event->pos().x();
	int y = event->pos().y();
	
	startPoint = Point(x, y);
	emit setStart(startPoint);
	
	painter->begin(img);
	img->fill(painter->getColorBg());
	painter->drawLineSeg(x - 4, y, x + 4, y);
	painter->drawLineSeg(x, y - 4, x, y + 4);
	painter->end();
	repaint();
}
