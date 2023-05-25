#include "SteadyMissile.h"

SteadyMissile::SteadyMissile(const char* __image_path, int __init_x, int __init_y, int __speed_x,
                             int __speed_y, int __attack_point)
    : _Missile(__image_path, __init_x, __init_y), _speed_x(__speed_x), _speed_y(__speed_y),
      _attack_point(__attack_point) {}

void SteadyMissile::collide(_Plane* plane) {
	if (plane->box().intersects(_rect)) {
		_free = true;
		plane->health() -= _attack_point;
	}
}

void SteadyMissile::updatePosition() {
	_rect.moveTo(_rect.x() + _speed_x, _rect.y() + _speed_y);
}


SteadyMissileF::SteadyMissileF(const char* __image_path, int __init_x, int __init_y,
                               double __speed_x, double __speed_y, int __attack_point)
    : _Missile(__image_path, __init_x, __init_y), _real_x(__init_x), _real_y(__init_y),
      _speed_x(__speed_x), _speed_y(__speed_y), _attack_point(__attack_point) {}

void SteadyMissileF::collide(_Plane* plane) {
	if (plane->box().intersects(_rect)) {
		_free = true;
		plane->health() -= _attack_point;
	}
}

void SteadyMissileF::updatePosition() {
	_rect.moveTo(_real_x += _speed_x, _real_y += _speed_y);
}
