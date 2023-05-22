#pragma once
#include "_Plane.h"
#include "BattleField.h"

class BattleField;

class EnemyPlane : public _Plane {
protected:
	void _setPosition(int __x, int __y) override;
	int shoot;

public:
	EnemyPlane(const char* __image_path, int __health, QPoint __init_pos);

public:
	virtual void shootMissiles(BattleField* field) = 0;
	virtual void updatePosition() = 0;
};

class TrivialEnemyPlane : public EnemyPlane {
private:
	int _timer, _speed_x, _speed_y;


public:
	TrivialEnemyPlane(const char* __image_path, int __health);

public:
	void updatePosition() final;
	void shootMissiles(BattleField* field);
	QPolygon box() const final;
};
