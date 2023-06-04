#include "ShieldBonus.h"
#include "PlayerPlane.h"

static constexpr const char* shield_bonus_path = ":/PlaneFight/img/bonus/shield_bonus.png";

ShieldBonus::ShieldBonus(double __init_x, double __init_y, double __speed_x, double __speed_y)
    : _Bonus(shield_bonus_path, __init_x, __init_y), _speed_x(__speed_x), _speed_y(__speed_y) {}

void ShieldBonus::updatePosition() {
	_rect.moveTo(_rect.x() + _speed_x, _rect.y() + _speed_y);
}
void ShieldBonus::collide() {
	if (PlayerPlane::plane()->rect().intersects(_rect)) {
		_free = true;
		PlayerPlane::plane()->buff.shield = 3 * (1000 / update_rate);
	}
}
