#pragma once
#include "_Entity.h"


class LifeBonus : public _Bonus {
private:
	int _speed_x, _speed_y;
	int _heal_point;

public:
	LifeBonus(const char* __image_path, int __init_x, int __init_y, int __speed_x, int __speed_y,
	          int __heal_point);

public:
	void updatePosition() final;
	void collide() final;
};
