#include "_Entity.h"
#include "_Plane.h"

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
_Entity::_Entity(const char* const __image_path, int __init_x, int __init_y) {
	_picture.load(__image_path);
	_rect.setWidth(_picture.width());
	_rect.setHeight(_picture.height());
	_rect.moveTo(__init_x - _picture.width() / 2, __init_y - _picture.height() / 2);
}

const QPixmap& _Entity::picture() const {
	return _picture;
}
const QRect& _Entity::rect() const {
	return _rect;
}
bool _Entity::free() const {
	return _free || _rect.bottom() > battlefield_border.bottom();
}