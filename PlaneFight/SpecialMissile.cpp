#include "SpecialMissile.h"

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