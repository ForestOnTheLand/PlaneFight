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
	virtual bool free() const;

public:
	virtual void updatePosition() = 0;    // To be implemented...
};


class _Plane : public _Entity {
protected:
	int _health;

protected:
	virtual void _setPosition(double __x, double __y);

public:
	_Plane(const char* const __image_path, QPointF __init_pos, int __health);
	virtual ~_Plane() = default;

public:
	virtual QPolygonF box() const;
	int health() const;
	bool dead() const;

public:
	void setPosition(double __x, double __y);
	void setPosition(QPointF p);
	void moveBy(double __dx, double __dy);
	virtual void changeHealth(int m);
	virtual void attack(_Plane* __other);
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
