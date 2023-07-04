#include "Missile.h"
#include "PlayerPlane.h"

SpecialMissile::SpecialMissile(std::initializer_list<const char*> __image_path, double __init_x,
                               double __init_y, double __speed)
    : _Effect(__image_path), _Missile(*__image_path.begin(), __init_x, __init_y), _speed(__speed) {}

void SpecialMissile::updatePosition() {
	_rect.translate(0, -_speed);
	++_timer;
}

void SpecialMissile::collide(_Plane* plane) {
	if (plane->box().intersects(_rect)) {
		plane->changeHealth(-10000);
		if (plane->health() > 0) {
			_free = true;
		}
	}
}

void SpecialMissile::display(QPainter& painter) {
	if (_timer == 10) {
		_timer = 0;
		if (++_picture_index == _pictures.size()) {
			_picture_index = 0;
		}
	}
	QPixmap& picture = *_pictures[_picture_index];
	painter.drawPixmap(_rect.center().x() - picture.width() / 2.0,
	                   _rect.center().y() - picture.height() / 2.0, picture);
}

SteadyMissile::SteadyMissile(const char* __image_path, double __init_x, double __init_y,
                             double __speed_x, double __speed_y, int __attack_point)
    : _Missile(__image_path, __init_x, __init_y), _speed_x(__speed_x), _speed_y(__speed_y),
      _attack_point(__attack_point) {}

void SteadyMissile::collide(_Plane* plane) {
	if (plane->box().intersects(_rect)) {
		_free = true;
		plane->changeHealth(-_attack_point);
	}
}

void SteadyMissile::updatePosition() {
	_rect.moveTo(_rect.x() + _speed_x, _rect.y() + _speed_y);
}



TrackMissile::TrackMissile(const char* __image_path, double __init_x, double __init_y,
                           double __speed_x, double __speed_y, int __attack_point, int __track_time,
                           int __stop_time)
    : _Missile(__image_path, __init_x, __init_y), _real_x(__init_x), _real_y(__init_y),
      _speed_x(__speed_x), _speed_y(__speed_y), _attack_point(__attack_point),
      _track_time(__track_time), _stop_time(__stop_time) {}

void TrackMissile::collide(_Plane* plane) {
	if (plane->box().intersects(_rect)) {
		_free = true;
		plane->changeHealth(-_attack_point);
	}
}

void TrackMissile::updatePosition() {
	if (_timer++ == _track_time + _stop_time) {
		double dx = PlayerPlane::plane()->rect().center().x() - rect().center().x();
		double dy = PlayerPlane::plane()->rect().center().y() - rect().center().y();
		double distance = sqrt(dx * dx + dy * dy);
		double speed = sqrt(_speed_x * _speed_x + _speed_y * _speed_y);
		_speed_x = speed * dx / distance;
		_speed_y = speed * dy / distance;
	}
	if (_timer++ >= _track_time && _timer <= _track_time + _stop_time) {
		return;
	}
	_rect.moveTo(_real_x += _speed_x, _real_y += _speed_y);
}
