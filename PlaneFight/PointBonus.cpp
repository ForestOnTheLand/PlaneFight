#include "PointBonus.h"
#include "_Plane.h"


PointBonus::PointBonus(const char* __image_path, int __init_x, int __init_y, int __speed_x,
	int __speed_y,int __heal_point):_Missile(__image_path, __init_x, __init_y), 
	_speed_x(__speed_x), _speed_y(__speed_y),_heal_point(__heal_point) {}

void PointBonus::collide(_Plane* plane) {
	if (plane->rect().intersects(_rect)) {
		_free = true;
		plane->health() += _heal_point;
	}
}

void PointBonus::updatePosition() {
	_rect.moveTo(_rect.x() + _speed_x, _rect.y() + _speed_y);
}
