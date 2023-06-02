#pragma once
#include "_Entity.h"


class PowerBonus : public _Bonus {
private:
	double _speed_x, _speed_y;
	int _strengthen_point;

public:
	PowerBonus(double __init_x, double __init_y, double __speed_x, double __speed_y,
	           int __strengthen_point);

public:
	void updatePosition() final;
	void collide() final;
};
