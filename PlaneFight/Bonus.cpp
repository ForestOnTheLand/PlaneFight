#include "Bonus.h"
#include "PlayerPlane.h"

static constexpr const char* life_drop_path = ":/PlaneFight/img/life.png";
static constexpr const char* point_drop_path = ":/PlaneFight/img/point.png";
static constexpr const char* power_drop_path = ":/PlaneFight/img/power.png";
static constexpr const char* shield_bonus_path = ":/PlaneFight/img/bonus/shield_bonus.png";

LifeBonus::LifeBonus(double __init_x, double __init_y, double __speed_x, double __speed_y,
                     int __heal_point)
    : _Bonus(life_drop_path, __init_x, __init_y, __speed_x, __speed_y), _heal_point(__heal_point) {}

void LifeBonus::collide() {
	if (PlayerPlane::plane()->rect().intersects(_rect)) {
		_free = true;
		PlayerPlane::plane()->changeHealth(_heal_point);
	}
}


PointBonus::PointBonus(double __init_x, double __init_y, double __speed_x, double __speed_y,
                       int __point)
    : _Bonus(point_drop_path, __init_x, __init_y, __speed_x, __speed_y), _point(__point) {}

void PointBonus::collide() {
	if (PlayerPlane::plane()->rect().intersects(_rect)) {
		_free = true;
		PlayerPlane::plane()->score += _point;
	}
}


PowerBonus::PowerBonus(double __init_x, double __init_y, double __speed_x, double __speed_y,
                       int __strengthen_point)
    : _Bonus(power_drop_path, __init_x, __init_y, __speed_x, __speed_y),
      _strengthen_point(__strengthen_point) {}

void PowerBonus::collide() {
	if (PlayerPlane::plane()->rect().intersects(_rect)) {
		_free = true;
		PlayerPlane::plane()->power += _strengthen_point;
	}
}


ShieldBonus::ShieldBonus(double __init_x, double __init_y, double __speed_x, double __speed_y)
    : _Bonus(shield_bonus_path, __init_x, __init_y, __speed_x, __speed_y) {}

void ShieldBonus::collide() {
	if (PlayerPlane::plane()->rect().intersects(_rect)) {
		_free = true;
		PlayerPlane::plane()->buff.shield = 5 * (1000 / update_rate);
	}
}