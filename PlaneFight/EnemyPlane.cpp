#include "EnemyPlane.h"
#include "PlayerPlane.h"
#include "_Missile.h"
#include "SteadyMissile.h"
#include "BattleField.h"
#include "PointBonus.h"
#include "util.h"

static constexpr int trival_plane_shoot_interval = 50;
static constexpr const char* trival_missile_path = ":/PlaneFight/img/bullet/mid_bullet_green.png";
static constexpr const char* point_drop_path = ":/PlaneFight/img/P.png";



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
		field->_enemyMissile.push_back(new SteadyMissile(trival_missile_path, _rect.center().x(),
			_rect.center().y() - 20, 0, 5, 50));
	}

	return;
}

void TrivialEnemyPlane::Drop(BattleField* field) {
	if (with_probability(0.2)) {
		field->_enemyDrop.push_back(new PointBonus(point_drop_path, _rect.center().x(),
			_rect.center().y(), 0, 4, 10));
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
