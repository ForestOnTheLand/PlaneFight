#pragma once

#include "util.h"

/**
 * Abstract Base Class for all Entities.
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
	int health();
	bool dead() const;
	virtual bool out() const;

public:
	virtual void changeHealth(int m);
	void setPosition(double __x, double __y);
	void setPosition(QPointF p);
	void moveBy(double __dx, double __dy);
	virtual void hurt(_Plane* __other);
	virtual void drawOn(QPainter& painter);
};


class _Missile : public _Entity {
public:
	explicit _Missile(const char* const __image_path, double __init_x, double __init_y);
	virtual void collide(_Plane* plane) = 0;
};


class _Bonus : public _Entity {
protected:
	double _speed_x, _speed_y;

public:
	explicit _Bonus(const char* const __image_path, double __init_x, double __init_y,
	                double __speed_x, double __speed_y);
	void updatePosition() override;
	virtual void collide() = 0;
};
