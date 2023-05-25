#pragma once
#include "_Plane.h"

class BattleField;

class EnemyPlane : public _Plane {
protected:
	void _setPosition(int __x, int __y) override;
	int _timer;

public:
	EnemyPlane(const char* __image_path, int __health, QPoint __init_pos);

public:
	virtual void shootMissiles(BattleField* field) = 0;
	virtual void Drop(BattleField* field) = 0;
	virtual void updatePosition() = 0;
	QPolygon box() const override;
};


class TrivialEnemyPlane : public EnemyPlane {
private:
	int _speed_x, _speed_y;

public:
	TrivialEnemyPlane(const char* __image_path, int __health);

public:
	void updatePosition() final;
	void shootMissiles(BattleField* field) final;
	void Drop(BattleField* field) final;
};


class StableEnemyPlane : public EnemyPlane {
private:
	int _speed_x, _speed_y;
	int _height;

public:
	StableEnemyPlane(const char* __image_path, int __health, int __height);

public:
	void updatePosition() final;
	void shootMissiles(BattleField* field) final;
	void Drop(BattleField* field) final;
};
