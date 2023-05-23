#include "LifeBonus.h"
#include "PlayerPlane.h"


LifeBonus::LifeBonus(const char* __image_path, int __init_x, int __init_y, int __speed_x,
                     int __speed_y, int __heal_point)
    : _Bonus(__image_path, __init_x, __init_y), _speed_x(__speed_x), _speed_y(__speed_y),
      _heal_point(__heal_point) {}

void LifeBonus::collide() {
	if (PlayerPlane::plane()->rect().intersects(_rect)) {
		_free = true;
		PlayerPlane::plane()->health() += _heal_point;
		if (PlayerPlane::plane()->health() > player_max_health) {
			PlayerPlane::plane()->health() = player_max_health;
		}
	}
}

void LifeBonus::updatePosition() {
	_rect.moveTo(_rect.x() + _speed_x, _rect.y() + _speed_y);
}
