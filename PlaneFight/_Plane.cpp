#include "_Plane.h"
#include "_Missile.h"

const QPixmap& _Plane::picture() const {
	return _picture;
}
const QRect& _Plane::rect() const {
	return _rect;
}
const QPolygon& _Plane::border() const {
	return _border;
}

/**
 * Constructor of _Plane
 *
 * \param __image_path :  Path of the picture of plane
 */
_Plane::_Plane(const char* const __image_path) {
	_picture.load(__image_path);
	_rect.setWidth(_picture.width());
	_rect.setHeight(_picture.height());
	_rect.moveTo(0, 0);
}

/**
 *
 * \param __x :  x axis coordinate of the center of plane
 * \param __y :  y axis coordinate of the center of plane
 */
void _Plane::setPosition(int __x, int __y) {
	_rect.moveTo(__x - _picture.width() / 2, __y - _picture.height() / 2);
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
