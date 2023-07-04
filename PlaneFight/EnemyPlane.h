#pragma once
#include "_Entity.h"

class BattleField;

class _EnemyPlane : public _Plane {
protected:
	void _setPosition(double __x, double __y) override;
	virtual void _clearOut();

public:
	_EnemyPlane(const char* __image_path, int __health, QPointF __init_pos);

public:
	virtual void shootMissiles(BattleField* field) = 0;
	virtual void afterDeath(BattleField* field) = 0;

	friend class EnemyClearingPolicy;
};


class EnemyPlane : public _EnemyPlane {
	std::function<int(int)> _x, _y;
	std::function<void(EnemyPlane*, BattleField*)> _shoot;
	std::vector<double> _prob;
	int _shoot_timer = 0, _move_timer = 0, _shoot_interval;

private:
	void _clearOut() override;

public:
	EnemyPlane(const char* __image_path, int __health, int __shoot_interval,
	           std::function<void(EnemyPlane*, BattleField*)> __shoot,
	           std::function<double(int)> __x, std::function<double(int)> __y,
	           std::initializer_list<double> __prob);
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
		class Track {
		public:
			Track() = default;
			void operator()(EnemyPlane* plane, BattleField* field);
		};
	}    // namespace Shoot

	namespace Speed {
		class Steady {
			double _init, _v;

		public:
			explicit Steady(double __init, double __v = 0);
			double operator()(int t);
		};

		class Stable {
			double _init, _v;
			double _limit;
			int _limit_time;

		public:
			explicit Stable(double __init, double __v, double __limit, int __limit_time);
			double operator()(int t);
		};

		class RandomX {
			double _speed = 0, _before = random_x(), _timer = 0;

		public:
			RandomX() = default;
			double operator()(int t);
		};
	}    // namespace Speed
	namespace Timer {
		class Gap {
			int _time;
			int _timer = 0;

		public:
			inline explicit Gap(int __time) : _time(__time) {}
			inline bool operator()() {
				if (++_timer >= _time) {
					_timer = 0;
					return true;
				} else {
					return false;
				}
			}
		};
	}    // namespace Timer
}    // namespace Plane
