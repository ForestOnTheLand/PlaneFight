#include "EnemyPlane.h"
#include "PlayerPlane.h"
#include "_Entity.h"
#include "SteadyMissile.h"
#include "ArbitraryMissile.h"
#include "BattleField.h"
#include "PointBonus.h"
#include "PowerBonus.h"
#include "LifeBonus.h"
#include "util.h"

static constexpr int trival_plane_shoot_interval = 50;
static constexpr int stable_plane_shoot_interval = 80;
static constexpr const char* trival_missile_path = ":/PlaneFight/img/bullet/mid_bullet_green.png";
static constexpr const char* stable_missile_path = ":/PlaneFight/img/bullet/small_bullet_purple.png";
static constexpr const char* life_drop_path = ":/PlaneFight/img/life.png";
static constexpr const char* point_drop_path = ":/PlaneFight/img/point.png";
static constexpr const char* power_drop_path = ":/PlaneFight/img/power.png";



EnemyPlane::EnemyPlane(const char* __image_path, int __health, QPoint __init_pos)
    : _Plane(__image_path, __health) {
	setPosition(__init_pos);
	shoot = 0;
}

void EnemyPlane::_setPosition(int __x, int __y) {
	_rect.moveCenter({_checked(__x, battlefield_border.left() + _rect.width() / 2,
	                           battlefield_border.right() - _rect.width() / 2),
	                  std::max(__y, battlefield_border.top() + _rect.height() / 2)});
}


TrivialEnemyPlane::TrivialEnemyPlane(const char* __image_path, int __health)
    : EnemyPlane(__image_path, __health,
                 {randint(battlefield_border.left() + _rect.width() / 2,
                          battlefield_border.right() - _rect.width() / 2),
                  0}),
      _timer(randint(1, 50)), _speed_x(randint(-3, 4)), _speed_y(3) {}

void TrivialEnemyPlane::shootMissiles(BattleField* field) {
	if (++shoot == trival_plane_shoot_interval) {
		shoot = 0;
		field->_enemyMissile.push_back(new ArbitraryMissile(trival_missile_path, _rect.center().x(),
		                                                 _rect.center().y() - 20, 0, 5, 50));
	}

	return;
}

void TrivialEnemyPlane::Drop(BattleField* field) {
	if (with_probability(0.2)) {
		field->_drops.push_back(
		    new PointBonus(point_drop_path, _rect.center().x(), _rect.center().y(), 0, 4, 10));
	} else if (with_probability(0.2)) {
		field->_drops.push_back(
		    new PowerBonus(power_drop_path, _rect.center().x(), _rect.center().y(), 0, 4, 5));
	} else if (with_probability(0.2)) {
		field->_drops.push_back(
		    new LifeBonus(life_drop_path, _rect.center().x(), _rect.center().y(), 0, 4, 10));
	}


	return;
}



QPolygon TrivialEnemyPlane::box() const {
	return QPolygon(_rect);
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
		{ randint(battlefield_border.left() + _rect.width() / 2,
				 battlefield_border.right() - _rect.width() / 2),
		 0 }),
	_timer(randint(1, 50)), _speed_x(0), _speed_y(3),_height(__height) {}

void StableEnemyPlane::shootMissiles(BattleField* field) {
	if (++shoot == stable_plane_shoot_interval) {
		shoot = 0;
		field->_enemyMissile.push_back(new SteadyMissile(stable_missile_path, _rect.center().x(),
			_rect.center().y() - 20, 0, 5, 50));
		field->_enemyMissile.push_back(new SteadyMissile(stable_missile_path, _rect.center().x(),
			_rect.center().y() - 20, -2, 3, 50));
		field->_enemyMissile.push_back(new SteadyMissile(stable_missile_path, _rect.center().x(),
			_rect.center().y() - 20, 2, 3, 50));
	}

	return;
}

void StableEnemyPlane::Drop(BattleField* field) {
	if (with_probability(0.2)) {
		field->_drops.push_back(new PointBonus(point_drop_path, _rect.center().x(),
			_rect.center().y(), 0, 4, 10));
	}
	else if (with_probability(0.2)) {
		field->_drops.push_back(new PowerBonus(power_drop_path, _rect.center().x(),
			_rect.center().y(), 0, 4, 2));
	}
	else if (with_probability(0.2)) {
		field->_drops.push_back(new LifeBonus(life_drop_path, _rect.center().x(),
			_rect.center().y(), 0, 4, 10));
	}


	return;
}




QPolygon StableEnemyPlane::box() const {
	return QPolygon(_rect);
}

void StableEnemyPlane::updatePosition() {
	if (_rect.center().y() < _height) {
		moveBy(_speed_x, _speed_y);
	}
}