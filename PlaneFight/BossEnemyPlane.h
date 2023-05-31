#pragma once
#include "EnemyPlane.h"
#include "Laser.h"

class BossEnemyPlane : public _EnemyPlane {
private:
	void shootMissilesAround(BattleField* field);
	void shootMissilesArc(BattleField* field);
	void shootMissilesRound(BattleField* field);
	void shootMissilesTrack(BattleField* field);
	void shootLaser(BattleField* field);
	int _shoot_state = 0;
	int _max_health;
	Laser _laser;

public:
	BossEnemyPlane(const char* __image_path, int __health);
	void updatePosition() final;
	void shootMissiles(BattleField* field) final;
	void afterDeath(BattleField* field) final;
	void drawOn(QPainter& painter) final;
	bool out() const final;
	void hurt(_Plane* plane) final;
};