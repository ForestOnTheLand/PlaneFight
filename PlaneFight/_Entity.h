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
	virtual void updatePosition() = 0;    // To be implemented...
};

class _Missile : public _Entity {
public:
	explicit _Missile(const char* const __image_path, int __init_x, int __init_y);

public:
	virtual void collide(_Plane* plane) = 0;
};

class _Bonus : public _Entity {
public:
	explicit _Bonus(const char* const __image_path, int __init_x, int __init_y);

public:
	virtual void collide() = 0;
};
