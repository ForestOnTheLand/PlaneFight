#pragma once
#include "util.h"
#include "_Plane.h"
#include "_Entity.h"
#include "_Effect.h"

class SpecialMissile : public _Effect,
                       public _Missile {
	double _speed;
	int _timer = 0;

public:
	explicit SpecialMissile(std::initializer_list<const char*> __image_path, double __init_x,
	                        double __init_y, double __speed);
	void updatePosition() final;
	void collide(_Plane* plane) final;
	void display(QPainter& painter) final;
};
