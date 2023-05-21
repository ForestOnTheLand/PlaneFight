#include "EnemyPlane.h"
#include "PlayerPlane.h"
#include "_Missile.h"

EnemyPlane::EnemyPlane(const char* __image_path, int __health, QPoint __init_pos)
    : _Plane(__image_path, __health) {
	setPosition(__init_pos);
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

void TrivialEnemyPlane::shootMissiles() {
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
