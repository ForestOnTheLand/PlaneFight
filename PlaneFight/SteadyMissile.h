#pragma once
#include "_Plane.h"

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

class SteadyMissileF : public _Missile {
private:
	double _speed_x, _speed_y;
	double _real_x, _real_y;
	int _attack_point;

public:
	SteadyMissileF(const char* __image_path, int __init_x, int __init_y, double __speed_x,
	               double __speed_y, int __attack_point);

public:
	void updatePosition() final;
	void collide(_Plane* plane) final;
};
