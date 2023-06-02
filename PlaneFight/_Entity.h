#pragma once

#include "util.h"

class _Plane;

/**
 * Abstract Base Class for all Missiles.
 */
class _Entity {
protected:
	QPixmap _picture;
	QRectF _rect;
	bool _free = false;

public:
	explicit _Entity(const char* const __image_path, double __init_x, double __init_y);
	virtual ~_Entity() = default;

public:
	const QPixmap& picture() const;
	const QRectF& rect() const;
	bool free() const;

public:
	virtual void updatePosition() = 0;    // To be implemented...
};

class _Missile : public _Entity {
public:
	explicit _Missile(const char* const __image_path, double __init_x, double __init_y);

public:
	virtual void collide(_Plane* plane) = 0;
};

class _Bonus : public _Entity {
public:
	explicit _Bonus(const char* const __image_path, double __init_x, double __init_y);

public:
	virtual void collide() = 0;
};
