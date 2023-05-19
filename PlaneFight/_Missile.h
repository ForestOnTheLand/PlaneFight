#pragma once

#include "config.h"
#include <qpixmap.h>

class _Plane;

/**
 * Abstract Base Class for all Missiles.
 */
class _Missile {
protected:
	QPixmap _picture;
	QRect _rect;
	bool _free;
	int _attack;

public:
	const QPixmap& picture() const;
	const QRect& rect() const;
	bool free() const;
	int attack() const;

public:
	explicit _Missile(const char* const __image_path, int __init_x, int __init_y);
	virtual ~_Missile() = default;
	virtual void updatePosition() = 0;    // To be implemented...
};
