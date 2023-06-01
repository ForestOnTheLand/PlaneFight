#pragma once
#include "util.h"

class Laser {
private:
	int _width = 10;

public:
	QPoint src;
	double theta = 0.0;
	Laser() = default;
	void hurt();
	void drawOn(QPainter& painter);
};
