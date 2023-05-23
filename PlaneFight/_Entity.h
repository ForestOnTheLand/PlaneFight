#pragma once

#include "config.h"
#include <QPixmap>

class _Plane;

/**
 * Abstract Base Class for all Missiles.
 */
class _Entity {
protected:
	QPixmap _picture;
	QRect _rect;
	bool _free = false;

public:
	explicit _Entity(const char* const __image_path, int __init_x, int __init_y);
	virtual ~_Entity() = default;

public:
	const QPixmap& picture() const;
	const QRect& rect() const;
	bool free() const;

public:
	virtual void collide(_Plane* plane) = 0;
	virtual void updatePosition() = 0;    // To be implemented...
};
