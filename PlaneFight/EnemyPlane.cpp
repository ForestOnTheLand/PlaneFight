#include "EnemyPlane.h"
#include "PlayerPlane.h"
#include "SteadyMissile.h"
#include "BattleField.h"
#include "PointBonus.h"
#include "PowerBonus.h"
#include "LifeBonus.h"
#include <cmath>

static constexpr const char* trival_missile_path = ":/PlaneFight/img/bullet/mid_bullet_green.png";
static constexpr const char* stable_missile_path =
    ":/PlaneFight/img/bullet/small_bullet_purple.png";

_EnemyPlane::_EnemyPlane(const char* __image_path, int __health, QPoint __init_pos)
    : _Plane(__image_path, __health) {
	setPosition(__init_pos);
}

void _EnemyPlane::_setPosition(int __x, int __y) {
	_rect.moveCenter({_checked(__x, battlefield_border.left() + _rect.width() / 2,
	                           battlefield_border.right() - _rect.width() / 2),
	                  std::max(__y, battlefield_border.top() + _rect.height() / 2)});
}

QPolygon _EnemyPlane::box() const {
	return QPolygon(_rect);
}


EnemyPlane::EnemyPlane(const char* __image_path, int __health, int __shoot_inteval,
                       std::function<void(EnemyPlane*, BattleField*)> __shoot,
                       std::function<int(int)> __x, std::function<int(int)> __y,
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
	field->_effects.push_back(new ExplosionEffect(_rect.center()));
	_Bonus* bonus;
	switch (distribution_as(_prob)) {
		case 0: bonus = new PointBonus(_rect.center().x(), _rect.center().y(), 0, 4, 10); break;
		case 1: bonus = new PowerBonus(_rect.center().x(), _rect.center().y(), 0, 4, 5); break;
		case 2: bonus = new LifeBonus(_rect.center().x(), _rect.center().y(), 0, 4, 10); break;
		default: return;
	}
	field->_drops.push_back(bonus);
}
void EnemyPlane::updatePosition() {
	++_move_timer;
	_setPosition(_x(_move_timer), _y(_move_timer));
}

namespace Plane {
	namespace Shoot {
		void Straight::operator()(EnemyPlane* plane, BattleField* field) {
			field->_enemyMissile.push_back(new SteadyMissile(
			    trival_missile_path, plane->rect().center().x(), plane->rect().bottom(), 0, 5, 50));
		}
		void ThreeWays::operator()(EnemyPlane* plane, BattleField* field) {
			field->_enemyMissile.push_back(new SteadyMissile(
			    stable_missile_path, plane->rect().center().x(), plane->rect().bottom(), 0, 5, 50));
			field->_enemyMissile.push_back(new SteadyMissile(stable_missile_path,
			                                                 plane->rect().center().x(),
			                                                 plane->rect().bottom(), -2, 3, 50));
			field->_enemyMissile.push_back(new SteadyMissile(
			    stable_missile_path, plane->rect().center().x(), plane->rect().bottom(), 2, 3, 50));
		}
	}    // namespace Shoot
	namespace Speed {
		Steady::Steady(int __init, int __v) : _init(__init), _v(__v) {}
		int Steady::operator()(int t) {
			return t * _v + _init;
		}

		Stable::Stable(int __init, int __v, int __limit, int __limit_time)
		    : _init(__init), _v(__v), _limit(__limit), _limit_time(__limit_time) {}
		int Stable::operator()(int t) {
			return t < _limit_time ? std::min(t * _v + _init, _limit)
			                       : _limit + (t - _limit_time) * _v;
		}

		int RandomX::operator()(int t) {
			if (--_timer <= 0) {
				_timer = randint(1, 50);
				_speed = randint(-3, 4);
			}
			return _before += _speed;
		}
	}    // namespace Speed
}    // namespace Plane

#if 0
TrivialEnemyPlane::TrivialEnemyPlane(const char* __image_path, int __health)
    : _EnemyPlane(__image_path, __health,
                 {randint(battlefield_border.left() + _rect.width() / 2,
                          battlefield_border.right() - _rect.width() / 2),
                  0}),
      _speed_x(randint(-3, 4)), _speed_y(3) {}

void TrivialEnemyPlane::shootMissiles(BattleField* field) {
	if (++_timer == trival_plane_shoot_interval) {
		_timer = 0;
		field->_enemyMissile.push_back(new SteadyMissile(trival_missile_path, _rect.center().x(),
		                                                 _rect.center().y() + 20, 0, 5, 50));
	}
}

void TrivialEnemyPlane::Drop(BattleField* field) {
	if (with_probability(0.2)) {
		field->_drops.push_back(new PointBonus(_rect.center().x(), _rect.center().y(), 0, 4, 10));
	} else if (with_probability(0.2)) {
		field->_drops.push_back(new PowerBonus(_rect.center().x(), _rect.center().y(), 0, 4, 5));
	} else if (with_probability(0.2)) {
		field->_drops.push_back(new LifeBonus(_rect.center().x(), _rect.center().y(), 0, 4, 10));
	}
}

void TrivialEnemyPlane::updatePosition() {
	if (--_timer == 0) {
		_timer = randint(1, 50);
		_speed_x = randint(-3, 4);
	}
	moveBy(_speed_x, _speed_y);
}


StableEnemyPlane::StableEnemyPlane(const char* __image_path, int __health, int __height)
    : EnemyPlane(__image_path, __health,
                 {randint(battlefield_border.left() + _rect.width() / 2,
                          battlefield_border.right() - _rect.width() / 2),
                  0}),
      _speed_x(0), _speed_y(3), _height(__height) {}

void StableEnemyPlane::shootMissiles(BattleField* field) {
	if (++_timer == stable_plane_shoot_interval) {
		_timer = 0;
		field->_enemyMissile.push_back(new SteadyMissile(stable_missile_path, _rect.center().x(),
		                                                 _rect.center().y() - 20, 0, 5, 50));
		field->_enemyMissile.push_back(new SteadyMissile(stable_missile_path, _rect.center().x(),
		                                                 _rect.center().y() - 20, -2, 3, 50));
		field->_enemyMissile.push_back(new SteadyMissile(stable_missile_path, _rect.center().x(),
		                                                 _rect.center().y() - 20, 2, 3, 50));
	}
}

void StableEnemyPlane::Drop(BattleField* field) {
	if (with_probability(0.2)) {
		field->_drops.push_back(
		    new PointBonus(point_drop_path, _rect.center().x(), _rect.center().y(), 0, 4, 10));
	} else if (with_probability(0.2)) {
		field->_drops.push_back(
		    new PowerBonus(power_drop_path, _rect.center().x(), _rect.center().y(), 0, 4, 2));
	} else if (with_probability(0.2)) {
		field->_drops.push_back(
		    new LifeBonus(life_drop_path, _rect.center().x(), _rect.center().y(), 0, 4, 10));
	}
}

void StableEnemyPlane::updatePosition() {
	if (_rect.center().y() < _height) {
		moveBy(_speed_x, _speed_y);
	}
}
#endif