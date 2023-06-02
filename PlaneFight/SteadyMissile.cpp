#include "SteadyMissile.h"

SteadyMissile::SteadyMissile(const char* __image_path, double __init_x, double __init_y,
                             double __speed_x, double __speed_y, int __attack_point)
    : _Missile(__image_path, __init_x, __init_y), _speed_x(__speed_x), _speed_y(__speed_y),
      _attack_point(__attack_point) {}

void SteadyMissile::collide(_Plane* plane) {
	if (plane->box().intersects(_rect)) {
		_free = true;
		plane->hurtUpdate();
		plane->health() -= _attack_point;
	}
}

void SteadyMissile::updatePosition() {
	_rect.moveTo(_rect.x() + _speed_x, _rect.y() + _speed_y);
}
