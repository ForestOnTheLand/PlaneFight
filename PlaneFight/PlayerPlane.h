#pragma once

#include <vector>
#include "util.h"
#include "_Plane.h"

/**
 * Player's plane.
 * A Singleton class derived from class `_Plane`
 */
class PlayerPlane : public _Plane {
private:
	std::vector<_Missile*> _missiles;    // Missiles of plane
	static PlayerPlane* _plane;

private:
	PlayerPlane(const char* const __image_path);
	void _setPosition(int __x, int __y) final;
	PlayerPlane(const PlayerPlane&) = delete;
	PlayerPlane& operator=(const PlayerPlane&) = delete;

public:
	static PlayerPlane* plane();
	static void init();
	static void free();

public:
	void shootMissiles();
	void drawMissiles(QPainter& painter);
	void updateMissiles();
	void hurt(_Plane* __other) final;
	QPolygon box() const final;
};
