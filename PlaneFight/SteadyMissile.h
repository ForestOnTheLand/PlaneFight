#pragma once
#include "_Entity.h"

class _Plane;

class SteadyMissile : public _Missile {
private:
	int _speed_x, _speed_y;
	int _attack_point;

public:
	SteadyMissile(const char* __image_path, int __init_x, int __init_y, int __speed_x,
	              int __speed_y, int __attack_point);

public:
	void updatePosition() final;
	void collide(_Plane* plane) final;
};
