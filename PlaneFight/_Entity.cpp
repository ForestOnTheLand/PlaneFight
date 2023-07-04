#include "_Entity.h"

/*
    ######################################################################
    ##                          Class _Entity                          ##
    ######################################################################
*/

/**
 * \brief Constructor of missile
 * \param __image_path :  Path of the image of missile
 * \param __init_x :  initial x axis coordinate of the center of missile
 * \param __init_y :  initial y axis coordinate of the center of missile
 */
_Entity::_Entity(const char* const __image_path, double __init_x, double __init_y) {
	_picture.load(__image_path);
	_rect.setWidth(_picture.width());
	_rect.setHeight(_picture.height());
	_rect.moveTo(__init_x - _picture.width() / 2.0, __init_y - _picture.height() / 2.0);
}

const QPixmap& _Entity::picture() const {
	return _picture;
}
const QRectF& _Entity::rect() const {
	return _rect;
}
bool _Entity::free() const {
	return _free || !battlefield_border.intersects(_rect);
}

_Missile::_Missile(const char* const __image_path, double __init_x, double __init_y)
    : _Entity(__image_path, __init_x, __init_y) {}

_Bonus::_Bonus(const char* const __image_path, double __init_x, double __init_y, double __speed_x,
               double __speed_y)
    : _Entity(__image_path, __init_x, __init_y), _speed_x(__speed_x), _speed_y(__speed_y) {}
void _Bonus::updatePosition() {
	_rect.moveTo(_rect.x() + _speed_x, _rect.y() + _speed_y);
}

int _Plane::health() const {
	return _health;
}
void _Plane::changeHealth(int m) {
	_health += m;
}

/**
 * Constructor of _Plane
 *
 * \param __image_path :  Path of the picture of plane
 */
_Plane::_Plane(const char* const __image_path, QPointF __init_pos, int __health)
    : _Entity(__image_path, __init_pos.x(), __init_pos.y()), _health(__health) {}

QPolygonF _Plane::box() const {
	return QPolygonF(_rect);
}

void _Plane::_setPosition(double __x, double __y) {
	_rect.moveCenter({__x, __y});
}

void _Plane::setPosition(QPointF __p) {
	_setPosition(__p.x(), __p.y());
}

void _Plane::setPosition(double __x, double __y) {
	_setPosition(__x, __y);
}

/**
 *
 * \param __dx : change of x coordinate
 * \param __dy : change of y coordinate
 */
void _Plane::moveBy(double __dx, double __dy) {
	_setPosition(_rect.center().x() + __dx, _rect.center().y() + __dy);
}

void _Plane::attack(_Plane* __other) {
	if (box().intersects(__other->box())) {
		__other->changeHealth(-100);
	}
}

bool _Plane::dead() const {
	return (_health <= 0);
}



void _Plane::drawOn(QPainter& painter) {
	painter.drawPixmap(_rect, _picture, QRectF());
}