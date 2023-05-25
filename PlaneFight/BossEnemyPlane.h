#pragma once
#include "EnemyPlane.h"

class BossEnemyPlane : public EnemyPlane {
private:
	void shootMissilesAround(BattleField* field);
	void shootMissilesArc(BattleField* field);
	int _shoot_state = 0;
	int _max_health;

public:
	BossEnemyPlane(const char* __image_path, int __health);
	void updatePosition() final;
	void shootMissiles(BattleField* field) final;
	void Drop(BattleField* field) final;
	void drawOn(QPainter& painter) final;
	bool out() const final;
};