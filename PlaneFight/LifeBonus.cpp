#include "LifeBonus.h"
#include "PlayerPlane.h"

static constexpr const char* life_drop_path = ":/PlaneFight/img/life.png";

LifeBonus::LifeBonus(double __init_x, double __init_y, double __speed_x, double __speed_y,
                     int __heal_point)
    : _Bonus(life_drop_path, __init_x, __init_y), _speed_x(__speed_x), _speed_y(__speed_y),
      _heal_point(__heal_point) {}

void LifeBonus::collide() {
	if (PlayerPlane::plane()->rect().intersects(_rect)) {
		_free = true;
		PlayerPlane::plane()->changeHealth(_heal_point);
	}
}

void LifeBonus::updatePosition() {
	_rect.moveTo(_rect.x() + _speed_x, _rect.y() + _speed_y);
}
