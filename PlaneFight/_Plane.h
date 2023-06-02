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
	QRectF _rect;        // Border of picture
	int _health;

protected:
	virtual void _setPosition(double __x, double __y) = 0;

public:
	_Plane(const char* const __image_path, int __health);
	virtual ~_Plane() = default;

public:
	const QPixmap& picture() const;
	const QRectF& rect() const;
	virtual QPolygonF box() const = 0;
	int& health();
	bool dead() const;
	virtual bool out() const;

public:
	void setPosition(double __x, double __y);
	void setPosition(QPointF p);
	void moveBy(double __dx, double __dy);
	virtual void hurt(_Plane* __other);
	virtual void drawOn(QPainter& painter);
	virtual void hurtUpdate();
};
