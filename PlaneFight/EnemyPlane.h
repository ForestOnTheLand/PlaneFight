#pragma once
#include "_Plane.h"

class BattleField;

class _EnemyPlane : public _Plane {
protected:
	void _setPosition(int __x, int __y) override;

public:
	_EnemyPlane(const char* __image_path, int __health, QPoint __init_pos);

public:
	virtual void shootMissiles(BattleField* field) = 0;
	virtual void afterDeath(BattleField* field) = 0;
	virtual void updatePosition() = 0;
	QPolygon box() const override;
};


class EnemyPlane : public _EnemyPlane {
	std::function<int(int)> _x, _y;
	std::function<void(EnemyPlane*, BattleField*)> _shoot;
	std::initializer_list<double> _prob;
	int _shoot_timer = 0, _move_timer = 0, _shoot_interval;

public:
	EnemyPlane(const char* __image_path, int __health, int __shoot_interval,
	           std::function<void(EnemyPlane*, BattleField*)> __shoot, std::function<int(int)> __x,
	           std::function<int(int)> __y, std::initializer_list<double> __prob);
	void shootMissiles(BattleField* field) final;
	void afterDeath(BattleField* field) final;
	void updatePosition() final;
};

namespace Plane {
	namespace Shoot {
		class Straight {
		public:
			Straight() = default;
			void operator()(EnemyPlane* plane, BattleField* field);
		};
		class ThreeWays {
		public:
			ThreeWays() = default;
			void operator()(EnemyPlane* plane, BattleField* field);
		};
	}    // namespace Shoot

	namespace Speed {
		class Steady {
			int _init, _v;

		public:
			explicit Steady(int __init, int __v = 0);
			int operator()(int t);
		};

		class Stable {
			int _init, _v, _limit, _limit_time;

		public:
			explicit Stable(int __init, int __v, int __limit, int __limit_time);
			int operator()(int t);
		};

		class RandomX {
			int _speed = 0, _before = random_x(), _timer = 0;

		public:
			RandomX() = default;
			int operator()(int t);
		};
	}    // namespace Speed

}    // namespace Plane

#if 0
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
#endif