#pragma once

#include <qpainter.h>
#include "config.h"
#include <qpixmap.h>
#include <vector>

class _Missile;

/**
 * Abstract Base Class of all Planes.
 */
class _Plane {
protected:
	QPixmap _picture;                    // Picture of plane
	QRect _rect;                         // Border of picture
	std::vector<_Missile*> _missiles;    // Missiles of plane
	int _health;

public:
	const QPixmap& picture() const;
	const QRect& rect() const;

public:
	_Plane(const char* const __image_path, int __health);
	virtual ~_Plane() = default;

public:
	virtual void shootMissiles() = 0;
	int& health();
	void setPosition(int __x, int __y);
	void setPosition(QPoint __p);
	void updateMissiles();
	void drawMissiles(QPainter& painter);
	void hurt(_Plane* __other);
	bool dead();
};
