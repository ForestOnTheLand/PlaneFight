#pragma once
#include "_Missile.h"


class PowerBonus :public _Missile {
private:
	int _speed_x, _speed_y;
	int _strengthen_point;

public:
	PowerBonus(const char* __image_path, int __init_x, int __init_y, int __speed_x,
		int __speed_y, int __strengthen_point);

public:
	void updatePosition() final;
	void collide(_Plane* plane) final;
};

