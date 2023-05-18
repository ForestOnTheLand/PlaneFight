#include "PlayerPlane.h"
#include "SteadyMissile.h"

static constexpr const char* player_plane_path = ":/PlaneFight/img/player.png";    // @IMAGE

PlayerPlane* PlayerPlane::_plane = nullptr;

PlayerPlane::PlayerPlane(const char* const __image_path) : _Plane(__image_path) {}

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
		_missiles.push_back(
		    new SteadyMissile("", _rect.center().x(), _rect.center().y() - 20, 0, -10));
	}
}

PlayerPlane* PlayerPlane::plane() {
	return _plane;
}
