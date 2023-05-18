#pragma once
#include "_Plane.h"

class EnemyPlane : public _Plane {
public:
	EnemyPlane(const char* __image_path, QPoint __init_pos);

public:
	virtual void updatePosition() = 0;
};

class TrivialEnemyPlane : public EnemyPlane {
private:
	int _timer, _speed_x, _speed_y;

public:
	TrivialEnemyPlane(const char* __image_path);

public:
	void updatePosition() final;
	void shootMissiles() final;
};
