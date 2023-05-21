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

void _Plane::setPosition(QPoint __p) {
	_setPosition(__p.x(), __p.y());
}

void _Plane::setPosition(int __x, int __y) {
	_setPosition(__x, __y);
}

/**
 *
 * \param __dx : change of x coordinate
 * \param __dy : change of y coordinate
 */
void _Plane::moveBy(int __dx, int __dy) {
	_setPosition(_rect.center().x() + __dx, _rect.center().y() + __dy);
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
	if (box().intersects(__other->box())) {
		__other->health() = 0;
		this->_health = 0;
	}
	for (_Missile* missile : _missiles) {
		missile->hurt(__other);
	}
}

bool _Plane::dead() const {
	return (_health <= 0) || (_rect.y() >= battlefield_border.bottom());
}
