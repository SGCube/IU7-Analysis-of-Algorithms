#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

#include "point.h"
#include "lineseg.h"
#include "canvas.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	
private:
	Ui::MainWindow *ui;
	
	QImage img;
	Painter painter;
	QColor bgColor;
	
	std::vector<LineSeg> lineSegments;
	Point startPoint;
	LineSeg startLine;
	
signals:
	void ortDrawMode(bool isOrt);
	
public slots:
	void getStartPoint(Point p);

private slots:
	void on_lineColorBtn_clicked();
	void on_bgColorBtn_clicked();
	void on_iterBtn_clicked();
	void on_recBtn_clicked();
};
#endif // MAINWINDOW_H
