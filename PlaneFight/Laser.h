#pragma once
#include "util.h"

class Laser {
private:
	int _width = 10;
	QPixmap _picture;

public:
	QPoint src;
	double theta = 0.0;

public:
	Laser();
	void hurt();
	void drawOn(QPainter& painter);
};
