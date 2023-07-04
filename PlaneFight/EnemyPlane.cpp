#include "EnemyPlane.h"
#include "PlayerPlane.h"
#include "Missile.h"
#include "BattleField.h"
#include "Bonus.h"
#include <cmath>

static constexpr const char* trival_missile_path = ":/PlaneFight/img/bullet/mid_bullet_green.png";
static constexpr const char* stable_missile_path =
    ":/PlaneFight/img/bullet/small_bullet_darkBlue.png";
static constexpr const char* track_missile_path = ":/PlaneFight/img/bullet/small_bullet_orange.png";

_EnemyPlane::_EnemyPlane(const char* __image_path, int __health, QPointF __init_pos)
    : _Plane(__image_path, __init_pos, __health) {
	setPosition(__init_pos);
}

void _EnemyPlane::_setPosition(double __x, double __y) {
	_rect.moveCenter({__x, __y});
}

void _EnemyPlane::_clearOut() {
	return;
}

EnemyPlane::EnemyPlane(const char* __image_path, int __health, int __shoot_inteval,
                       std::function<void(EnemyPlane*, BattleField*)> __shoot,
                       std::function<double(int)> __x, std::function<double(int)> __y,
                       std::initializer_list<double> __prob)
    : _EnemyPlane(__image_path, __health, {__x(0), __y(0)}), _shoot_interval(__shoot_inteval),
      _shoot(__shoot), _x(__x), _y(__y), _prob(__prob) {}
void EnemyPlane::shootMissiles(BattleField* field) {
	if (++_shoot_timer >= _shoot_interval) {
		_shoot_timer = 0;
		_shoot(this, field);
	}
}
void EnemyPlane::afterDeath(BattleField* field) {
	field->effects.push_back(new ExplosionEffect(_rect.center()));
	_Bonus* bonus;
	switch (distribution_as(_prob)) {
		case 0: bonus = new PointBonus(_rect.center().x(), _rect.center().y(), 0, 4, 100); break;
		case 1: bonus = new PowerBonus(_rect.center().x(), _rect.center().y(), 0, 4, 5); break;
		case 2: bonus = new LifeBonus(_rect.center().x(), _rect.center().y(), 0, 4, 100); break;
		case 3: bonus = new ShieldBonus(_rect.center().x(), _rect.center().y(), 0, 4); break;
		default: return;
	}
	field->drops.push_back(bonus);
}
void EnemyPlane::updatePosition() {
	++_move_timer;
	_setPosition(_x(_move_timer), _y(_move_timer));
}

void EnemyPlane::_clearOut() {
	_x = Plane::Speed::Steady(_rect.center().x());
	_y = Plane::Speed::Steady(_rect.center().y() - _move_timer * 3, 3);
}

namespace Plane {
	namespace Shoot {
		void Straight::operator()(EnemyPlane* plane, BattleField* field) {
			field->enemy_missiles.push_back(new SteadyMissile(
			    trival_missile_path, plane->rect().center().x(), plane->rect().bottom(), 0, 5, 50));
		}
		void ThreeWays::operator()(EnemyPlane* plane, BattleField* field) {
			field->enemy_missiles.push_back(
			    new TrackMissile(track_missile_path, plane->rect().center().x(),
			                     plane->rect().center().y() + 20, 0, 5, 50, 30));
			field->enemy_missiles.push_back(new SteadyMissile(stable_missile_path,
			                                                  plane->rect().center().x(),
			                                                  plane->rect().bottom(), -2, 3, 50));
			field->enemy_missiles.push_back(new SteadyMissile(
			    stable_missile_path, plane->rect().center().x(), plane->rect().bottom(), 2, 3, 50));
		}
		void Track::operator()(EnemyPlane* plane, BattleField* field) {
			field->enemy_missiles.push_back(
			    new TrackMissile(track_missile_path, plane->rect().center().x(),
			                     plane->rect().center().y() + 20, 0, 5, 50, 0, 0));
		}
	}    // namespace Shoot
	namespace Speed {
		Steady::Steady(double __init, double __v) : _init(__init), _v(__v) {}
		double Steady::operator()(int t) {
			return t * _v + _init;
		}

		Stable::Stable(double __init, double __v, double __limit, int __limit_time)
		    : _init(__init), _v(__v), _limit(__limit), _limit_time(__limit_time) {}
		double Stable::operator()(int t) {
			return t < _limit_time ? std::min(t * _v + _init, _limit)
			                       : _limit + (t - _limit_time) * _v;
		}

		double RandomX::operator()(int t) {
			if (--_timer <= 0) {
				_timer = randint(1, 50);
				_speed = randint(-3, 4);
			}
			return _before += _speed;
		}
	}    // namespace Speed
}    // namespace Plane
