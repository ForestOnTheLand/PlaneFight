#pragma once
#include "_Entity.h"


class PointBonus : public _Bonus {
private:
	double _speed_x, _speed_y;
	int _point;

public:
	PointBonus(double __init_x, double __init_y, double __speed_x, double __speed_y, int __point);

public:
	void updatePosition() final;
	void collide() final;
};
