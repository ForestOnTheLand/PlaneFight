#include "EnemyPlane.h"

EnemyPlane::EnemyPlane(const char* __image_path, QPoint __init_pos) : _Plane(__image_path) {
	setPosition(__init_pos);
}

TrivialEnemyPlane::TrivialEnemyPlane(const char* __image_path)
    : EnemyPlane(__image_path, {rand() % BATTLEFIELD_WIDTH, 0}), _timer(rand() % 100 + 1),
      _speed_x(rand() % 11 - 5), _speed_y(30) {}

void TrivialEnemyPlane::shootMissiles() {
	return;
}

void TrivialEnemyPlane::updatePosition() {
	if (--_timer == 0) {
		_timer = rand() % 100 + 1;
		_speed_x = rand() % 11 - 5;
	}

	int _x = _rect.center().x() + _speed_x;
	int _y = _rect.center().y() + _speed_y;

	if (_x <= 0)
		_x = 0;
	else if (_x >= BATTLEFIELD_WIDTH)
		_x = BATTLEFIELD_WIDTH;

	setPosition(_x, _y);
}
