#include "PointBonus.h"
#include "_Plane.h"
#include "PlayerPlane.h"


PointBonus::PointBonus(const char* __image_path, int __init_x, int __init_y, int __speed_x,
	int __speed_y,int __point):_Missile(__image_path, __init_x, __init_y), 
	_speed_x(__speed_x), _speed_y(__speed_y),_point(__point) {}

void PointBonus::collide(_Plane* plane) {
	if (plane->rect().intersects(_rect)) {
		_free = true;
		PlayerPlane::plane()->score += _point;
	}
}

void PointBonus::updatePosition() {
	_rect.moveTo(_rect.x() + _speed_x, _rect.y() + _speed_y);
}
