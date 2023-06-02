#include "PointBonus.h"
#include "PlayerPlane.h"

static constexpr const char* point_drop_path = ":/PlaneFight/img/point.png";

PointBonus::PointBonus(double __init_x, double __init_y, double __speed_x, double __speed_y,
                       int __point)
    : _Bonus(point_drop_path, __init_x, __init_y), _speed_x(__speed_x), _speed_y(__speed_y),
      _point(__point) {}

void PointBonus::collide() {
	if (PlayerPlane::plane()->rect().intersects(_rect)) {
		_free = true;
		PlayerPlane::plane()->score += _point;
	}
}

void PointBonus::updatePosition() {
	_rect.moveTo(_rect.x() + _speed_x, _rect.y() + _speed_y);
}
