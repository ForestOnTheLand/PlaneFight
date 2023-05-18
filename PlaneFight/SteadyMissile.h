#pragma once
#include "_Missile.h"

class SteadyMissile : public _Missile {
private:
	int _speed_x, _speed_y;

public:
	SteadyMissile(const char* __image_path, int __init_x, int __init_y, int __speed_x,
	              int __speed_y);

public:
	void updatePosition() final;
};
