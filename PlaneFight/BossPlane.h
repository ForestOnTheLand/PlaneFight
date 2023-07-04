#pragma once
#include "EnemyPlane.h"
#include "Laser.h"

class BossPlane : public _EnemyPlane {
private:
	void shootMissilesAround(BattleField* field);
	void shootMissilesArc(BattleField* field);
	void shootMissilesRound(BattleField* field);
	void shootMissilesTrack(BattleField* field);
	void shootMissilesTarget(BattleField* field);
	void shootMissilesCrossing(BattleField* field);
	void shootLaser(BattleField* field);
	int _shoot_state = 0;
	int _max_health;
	int _attack;
	Laser _laser;

public:
	BossPlane(const char* __image_path, int __health, int __attack);
	void updatePosition() final;
	void shootMissiles(BattleField* field);
	void afterDeath(BattleField* field);
	void drawOn(QPainter& painter) final;
	bool free() const final;
	void attack(_Plane* plane) final;
};
