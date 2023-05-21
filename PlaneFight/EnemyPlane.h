#pragma once
#include "_Plane.h"

class EnemyPlane : public _Plane {
protected:
	void _setPosition(int __x, int __y) override;

public:
	EnemyPlane(const char* __image_path, int __health, QPoint __init_pos);

public:
	virtual void updatePosition() = 0;
};

class TrivialEnemyPlane : public EnemyPlane {
private:
	int _timer, _speed_x, _speed_y;

public:
	TrivialEnemyPlane(const char* __image_path, int __health);

public:
	void updatePosition() final;
	void shootMissiles() final;
	QPolygon box() const final;
};
