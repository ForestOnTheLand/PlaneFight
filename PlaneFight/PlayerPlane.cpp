#include "PlayerPlane.h"
#include "SteadyMissile.h"

static constexpr const char* player_plane_path = ":/PlaneFight/img/player.png";         // @IMAGE
static constexpr const char* player_missile_path = ":/PlaneFight/img/missile_0.png";    // @IMAGE
static constexpr int player_plane_health = 500;
static constexpr int player_plane_shoot_interval = 20;

PlayerPlane* PlayerPlane::_plane = nullptr;

PlayerPlane::PlayerPlane(const char* const __image_path)
    : _Plane(__image_path, player_plane_health) {}

void PlayerPlane::init() {
	_plane = new PlayerPlane(player_plane_path);
	_plane->setPosition(battlefield_border.center().x(),
	                    battlefield_border.bottom() - _plane->rect().height());
}

void PlayerPlane::free() {
	delete _plane;
	_plane = nullptr;
}

void PlayerPlane::shootMissiles() {
	static int timer = 0;
	if (++timer == player_plane_shoot_interval) {
		timer = 0;
		_missiles.push_back(new SteadyMissile(player_missile_path, _rect.center().x(),
		                                      _rect.center().y() - 20, 0, -10, 50));
	}
}

PlayerPlane* PlayerPlane::plane() {
	return _plane;
}

QPolygon PlayerPlane::box() const {
	return QPolygon({_rect.center()});
}

void PlayerPlane::_setPosition(int __x, int __y) {
	_rect.moveCenter({_checked(__x, battlefield_border.left() + _rect.width() / 2,
	                           battlefield_border.right() - _rect.width() / 2),
	                  _checked(__y, battlefield_border.top() + _rect.height() / 2,
	                           battlefield_border.bottom() - _rect.height() / 2)});
}
