#include "SteadyMissile.h"

SteadyMissile::SteadyMissile(const char* __image_path, int __init_x, int __init_y, int __speed_x,
                             int __speed_y)
    : _Missile(__image_path, __init_x, __init_y), _speed_x(__speed_x), _speed_y(__speed_y) {}

void SteadyMissile::updatePosition() {
	_rect.moveTo(_rect.x() + _speed_x, _rect.y() + _speed_y);
}
