#pragma once
#include "_Plane.h"

class SteadyMissile : public _Missile {
private:
	double _speed_x, _speed_y;
	int _attack_point;

public:
	SteadyMissile(const char* __image_path, double __init_x, double __init_y, double __speed_x,
	              double __speed_y, int __attack_point);

public:
	void updatePosition() final;
	void collide(_Plane* plane) final;
};
