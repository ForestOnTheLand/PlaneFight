#pragma once

#include "_Plane.h"
#include <vector>

/**
 * Player's plane.
 * A Singleton class derived from class `_Plane`
 */
class PlayerPlane : public _Plane {
private:
	int _hurt_state = 0;
	QPixmap _hurt_image;
	std::vector<_Missile*> _missiles;    // Missiles of plane
	static PlayerPlane* _plane;

private:
	PlayerPlane(const char* const __image_path, int _bombs);
	void _setPosition(double __x, double __y) final;
	PlayerPlane(const PlayerPlane&) = delete;
	PlayerPlane& operator=(const PlayerPlane&) = delete;

public:
	static PlayerPlane* plane();
	static void init();
	static void free();

public:
	int bombs;
	int score;
	int power;
	void shootMissiles();
	void Bomb();
	void drawMissiles(QPainter& painter);
	void drawHP(QPainter& painter);
	void updateMissiles();
	void hurt(_Plane* __other) final;
	QPolygonF box() const final;
	void drawOn(QPainter& painter) final;
	void hurtUpdate() final;
};
