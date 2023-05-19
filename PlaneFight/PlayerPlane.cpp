#include "PlayerPlane.h"
#include "SteadyMissile.h"

static constexpr const char* player_plane_path = ":/PlaneFight/img/player.png";         // @IMAGE
static constexpr const char* player_missile_path = ":/PlaneFight/img/missile_0.png";    // @IMAGE
static constexpr int player_plane_health = 500;

PlayerPlane* PlayerPlane::_plane = nullptr;

PlayerPlane::PlayerPlane(const char* const __image_path)
    : _Plane(__image_path, player_plane_health) {}

void PlayerPlane::init() {
	_plane = new PlayerPlane(player_plane_path);
}

void PlayerPlane::free() {
	delete _plane;
	_plane = nullptr;
}

void PlayerPlane::shootMissiles() {
	static int timer = 0;
	if (++timer == 50) {
		timer = 0;
		_missiles.push_back(new SteadyMissile(player_missile_path, _rect.center().x(),
		                                      _rect.center().y() - 20, 0, -10));
	}
}

PlayerPlane* PlayerPlane::plane() {
	return _plane;
}
