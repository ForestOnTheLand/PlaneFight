#pragma once
#include "_Plane.h"

class TrackMissile : public _Missile {
private:
	double _speed_x, _speed_y;
	double _real_x, _real_y;
	int _attack_point;
	int _track_time;
	int _timer = 0;

public:
	TrackMissile(const char* __image_path, double __init_x, double __init_y, double __speed_x,
	             double __speed_y, int __attack_point, int __track_time);

public:
	void updatePosition() final;
	void collide(_Plane* plane) final;
};
