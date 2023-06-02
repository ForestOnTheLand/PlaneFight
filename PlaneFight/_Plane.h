#pragma once

#include "util.h"
#include "_Entity.h"
#include <vector>

/**
 * Abstract Base Class of all Planes.
 */
class _Plane {
protected:
	QPixmap _picture;    // Picture of plane
	QRect _rect;         // Border of picture
	int _health;

protected:
	virtual void _setPosition(int __x, int __y) = 0;

public:
	_Plane(const char* const __image_path, int __health);
	virtual ~_Plane() = default;

public:
	const QPixmap& picture() const;
	const QRect& rect() const;
	virtual QPolygon box() const = 0;
	int& health();
	bool dead() const;
	virtual bool out() const;

public:
	void setPosition(int __x, int __y);
	void setPosition(QPoint p);
	void moveBy(int __dx, int __dy);
	virtual void hurt(_Plane* __other);
	virtual void drawOn(QPainter& painter);
	virtual void hurtUpdate();
};
