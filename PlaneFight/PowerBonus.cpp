#include "PowerBonus.h"
#include "PlayerPlane.h"

static constexpr const char* power_drop_path = ":/PlaneFight/img/power.png";

PowerBonus::PowerBonus(double __init_x, double __init_y, double __speed_x, double __speed_y,
                       int __strengthen_point)
    : _Bonus(power_drop_path, __init_x, __init_y), _speed_x(__speed_x), _speed_y(__speed_y),
      _strengthen_point(__strengthen_point) {}

void PowerBonus::collide() {
	if (PlayerPlane::plane()->rect().intersects(_rect)) {
		_free = true;
		PlayerPlane::plane()->power += _strengthen_point;
	}
}

void PowerBonus::updatePosition() {
	_rect.moveTo(_rect.x() + _speed_x, _rect.y() + _speed_y);
}
