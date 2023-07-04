#pragma once
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

class TrackMissile : public _Missile {
private:
	double _speed_x, _speed_y;
	double _real_x, _real_y;
	int _attack_point;
	int _track_time, _stop_time;
	int _timer = 0;

public:
	TrackMissile(const char* __image_path, double __init_x, double __init_y, double __speed_x,
	             double __speed_y, int __attack_point, int __track_time, int __stop_time = 30);

public:
	void updatePosition() final;
	void collide(_Plane* plane) final;
};
