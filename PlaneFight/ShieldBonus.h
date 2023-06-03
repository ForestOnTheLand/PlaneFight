#pragma once
#include "_Entity.h"

class ShieldBonus : public _Bonus {
private:
	double _speed_x, _speed_y;

public:
	ShieldBonus(double __init_x, double __init_y, double __speed_x, double __speed_y);

public:
	void updatePosition() final;
	void collide() final;
};
