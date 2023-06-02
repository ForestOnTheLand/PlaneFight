#include "TrackMissile.h"
#include "PlayerPlane.h"

TrackMissile::TrackMissile(const char* __image_path, double __init_x, double __init_y,
                           double __speed_x, double __speed_y, int __attack_point, int __track_time)
    : _Missile(__image_path, __init_x, __init_y), _real_x(__init_x), _real_y(__init_y),
      _speed_x(__speed_x), _speed_y(__speed_y), _attack_point(__attack_point),
      _track_time(__track_time) {}

void TrackMissile::collide(_Plane* plane) {
	if (plane->box().intersects(_rect)) {
		_free = true;
		plane->hurtUpdate();
		plane->health() -= _attack_point;
	}
}

void TrackMissile::updatePosition() {
	if (_timer++ == _track_time + 30) {
		double dx = PlayerPlane::plane()->rect().center().x() - rect().center().x();
		double dy = PlayerPlane::plane()->rect().center().y() - rect().center().y();
		double distance = sqrt(dx * dx + dy * dy);
		double speed = sqrt(_speed_x * _speed_x + _speed_y * _speed_y);
		_speed_x = speed * dx / distance;
		_speed_y = speed * dy / distance;
	}
	if (_timer++ >= _track_time && _timer <= _track_time + 30) {
		return;
	}
	_rect.moveTo(_real_x += _speed_x, _real_y += _speed_y);
}
