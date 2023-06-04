#pragma once

#include "_Plane.h"
#include "SpecialMissile.h"
#include <vector>

class BattleField;
/**
 * Player's plane.
 * A Singleton class derived from class `_Plane`
 */
class PlayerPlane : public _Plane {
private:
	int _hurt_state = 0, _cool_down_timer = 0;
	QPixmap _hurt_image, _shield_picture, _special_missile_icon;
	std::vector<_Missile*> _missiles;    // Missiles of plane
	SpecialMissile* _special_missile = nullptr;
	static PlayerPlane* _plane;
	static BattleField* _field;

private:
	PlayerPlane(const char* const __image_path, int _bombs);
	void _setPosition(double __x, double __y) final;
	PlayerPlane(const PlayerPlane&) = delete;
	PlayerPlane& operator=(const PlayerPlane&) = delete;

public:
	static PlayerPlane* plane();
	static void init(BattleField* b);
	static void free();

public:
	struct {
		int shield = 0;
	} buff;

public:
	int bombs;
	int score;
	int power;
	void shootMissiles();
	void Bomb();
	void shootUltimate();
	void drawMissiles(QPainter& painter);
	void drawHP(QPainter& painter);
	void updateMissiles();
	void hurt(_Plane* __other) final;
	QPolygonF box() const final;
	void drawOn(QPainter& painter) final;
	void drawCD(QPainter& painter);
	void changeHealth(int m) final;
};
