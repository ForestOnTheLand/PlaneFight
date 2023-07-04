#pragma once
#include "_Entity.h"


class LifeBonus : public _Bonus {
	int _heal_point;

public:
	LifeBonus(double __init_x, double __init_y, double __speed_x, double __speed_y,
	          int __heal_point);
	void collide() final;
};


class PointBonus : public _Bonus {
	int _point;

public:
	PointBonus(double __init_x, double __init_y, double __speed_x, double __speed_y, int __point);
	void collide() final;
};


class PowerBonus : public _Bonus {
	int _strengthen_point;

public:
	PowerBonus(double __init_x, double __init_y, double __speed_x, double __speed_y,
	           int __strengthen_point);
	void collide() final;
};


class ShieldBonus : public _Bonus {
public:
	ShieldBonus(double __init_x, double __init_y, double __speed_x, double __speed_y);
	void collide() final;
};
