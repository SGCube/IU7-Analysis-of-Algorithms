#include <QColorDialog>
#include <QMessageBox>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "fractal.h"

#ifdef _WIN32
#include <intrin.h>
uint64_t rdtsc() {
	return __rdtsc();
}
#else
uint64_t rdtsc() 
{
	unsigned int lo, hi;
	__asm__ __volatile__("rdtsc" : "=a" (lo), "=d" (hi));
	return ((uint64_t)hi << 32) | lo;
}
#endif

MainWindow::MainWindow(QWidget *parent):
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	img(700, 700, QImage::Format_RGB32),
	startPoint(0, 0),
	startLine(0, 0, 0, 0)
{
	ui->setupUi(this);
	ui->canvas->setCanvas(&img, &painter);
	img.fill(QColor(255, 255, 255));
	
	connect(ui->canvas, SIGNAL(setStart(Point)),
			this, SLOT(getStartPoint(Point)));
	
	QPixmap pxm(ui->lineColor->rect().size());
	pxm.fill(painter.getColorLine());
	ui->lineColor->setPixmap(pxm);
	
	pxm.fill(painter.getColorBg());
	ui->bgColor->setPixmap(pxm);
	bgColor = painter.getColorBg();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::getStartPoint(Point p)
{
	startPoint = p;
}

void MainWindow::on_lineColorBtn_clicked()
{
	QColor oldcolor = painter.getColorLine();
	QColor newcolor = QColorDialog::getColor(oldcolor, this);
	if (newcolor.isValid())
	{
		QPixmap pxm(ui->lineColor->rect().size());
		pxm.fill(newcolor);
		ui->lineColor->setPixmap(pxm);
		painter.setColorLine(newcolor);
	}
}

void MainWindow::on_bgColorBtn_clicked()
{
	QColor oldcolor = bgColor;
	QColor newcolor = QColorDialog::getColor(oldcolor, this);
	if (newcolor.isValid())
	{
		QPixmap pxm(ui->bgColor->rect().size());
		pxm.fill(newcolor);
		ui->bgColor->setPixmap(pxm);
		bgColor = newcolor;
		painter.setColorBg(newcolor);
		
		img.fill(bgColor);
		ui->canvas->repaint();
	}
}

void MainWindow::on_iterBtn_clicked()
{
    unsigned start_len = ui->lenSpinBox->value();
	unsigned n = ui->nSpinBox->value();
	
	Point nextPoint = Point(startPoint.x(), startPoint.y() - start_len);
	std::vector<Point> points = get_dragon_fractal(startPoint, nextPoint, n);
	
	img.fill(bgColor);
	ui->canvas->repaint();
	painter.begin(&img);
	painter.drawBrokenLine(points);
	painter.end();
	ui->canvas->repaint();
}

void MainWindow::on_recBtn_clicked()
{
	unsigned start_len = ui->lenSpinBox->value();
	unsigned n = ui->nSpinBox->value();
	
	Point nextPoint = Point(startPoint.x(), startPoint.y() - start_len);
	std::vector<Point> points({startPoint, nextPoint});
	points = get_dragon_fractal_rec(points, n);
	
	img.fill(bgColor);
	ui->canvas->repaint();
	painter.begin(&img);
	painter.drawBrokenLine(points);
	painter.end();
	ui->canvas->repaint();
}

void MainWindow::on_timeBtn_clicked()
{
	srand(time(NULL));
	
	std::ofstream file("time.csv");
	if (!file.is_open())
	{
		std::cout << "File open error!";
		return;
	}
	
	unsigned long long start_time = 0, end_time = 0;
	unsigned test_repeats = 100;
	file << "Size;Iter;Rec\n";
	Point nextPoint = Point(startPoint.x(), startPoint.y() - 1);
	
	for (unsigned n = 1; n <= 20; n++)
	{
		unsigned long long results[2] = { 0, 0 };
		for (unsigned k = 0; k < test_repeats; k++)
		{
			start_time = rdtsc();
			std::vector<Point> points = get_dragon_fractal(startPoint,
														   nextPoint, n);
			end_time = rdtsc();
			results[0] += end_time - start_time;

			start_time = rdtsc();
			std::vector<Point> points2({startPoint, nextPoint});
			points2 = get_dragon_fractal_rec(points2, n);
			end_time = rdtsc();
			results[1] += end_time - start_time;
		}
		file << n;
		for (unsigned k = 0; k < 2; k++)
		{
			results[k] /= test_repeats;
			file << ";" << results[k];
		}
		file << "\n";
	}
	
	file.close();
}
