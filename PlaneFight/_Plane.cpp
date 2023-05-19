#include "_Plane.h"
#include "_Missile.h"

const QPixmap& _Plane::picture() const {
	return _picture;
}
const QRect& _Plane::rect() const {
	return _rect;
}
int& _Plane::health() {
	return _health;
}

/**
 * Constructor of _Plane
 *
 * \param __image_path :  Path of the picture of plane
 */
_Plane::_Plane(const char* const __image_path, int __health) : _health(__health) {
	_picture.load(__image_path);
	_rect.setWidth(_picture.width());
	_rect.setHeight(_picture.height());
}

/**
 *
 * \param __x :  x axis coordinate of the center of plane
 * \param __y :  y axis coordinate of the center of plane
 */
void _Plane::setPosition(int __x, int __y) {
	_rect.moveCenter({__x, __y});
}

/**
 *
 * \param __p :  coordinate of the center of plane
 */
void _Plane::setPosition(QPoint __p) {
	setPosition(__p.x(), __p.y());
}

void _Plane::updateMissiles() {
	for (auto iter = _missiles.begin(); iter != _missiles.end();) {
		if ((*iter)->free()) {
			delete *iter;
			iter = _missiles.erase(iter);
		} else {
			(*iter)->updatePosition();
			++iter;
		}
	}
}

void _Plane::drawMissiles(QPainter& painter) {
	for (_Missile* missile : _missiles) {
		painter.drawPixmap(missile->rect(), missile->picture());
	}
}

void _Plane::hurt(_Plane* __other) {
	if (_rect.intersects(__other->rect())) {
		__other->health() = 0;
		this->_health = 0;
	}
	for (_Missile* missile : _missiles) {
		if (missile->rect().intersects(__other->rect()))
			__other->health() -= missile->attack();
	}
}

bool _Plane::dead() {
	return (_health <= 0) || (_rect.y() > BATTLEFIELD_HEIGHT + 5);
}
