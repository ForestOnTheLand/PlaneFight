#pragma once
#include "_Entity.h"


class LifeBonus : public _Bonus {
private:
	double _speed_x, _speed_y;
	int _heal_point;

public:
	LifeBonus(double __init_x, double __init_y, double __speed_x, double __speed_y,
	          int __heal_point);

public:
	void updatePosition() final;
	void collide() final;
};
