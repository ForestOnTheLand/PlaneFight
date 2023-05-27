#include "BossEnemyPlane.h"
#include "BattleField.h"
#include "SteadyMissile.h"

static constexpr const char* trival_missile_path = ":/PlaneFight/img/bullet/mid_bullet_green.png";

BossEnemyPlane::BossEnemyPlane(const char* __image_path, int __health)
    : _EnemyPlane(__image_path, __health, {battlefield_border.center().x(), 0}),
      _max_health(_health) {}

void BossEnemyPlane::shootMissilesAround(BattleField* field) {
	static double angle = 0;
	static int timer = 0;
	if (++timer <= 3)
		return;
	angle += 7, timer = 0;
	field->_enemyMissile.push_back(new SteadyMissileF(
	    trival_missile_path, _rect.center().x() + 10 * cos(angle),
	    _rect.center().y() + 10 * sin(angle), 2 * cos(angle), 2 * sin(angle), 50));
	if (angle > 720) {
		angle = 0, timer = 0;
		_shoot_state = 0;
	}
}

void BossEnemyPlane::shootMissilesArc(BattleField* field) {
	static int counter = 0;
	static int timer = 0;
	if (++timer <= 3)
		return;
	timer = 0;
	for (double angle = randdouble(40, 50); angle < 140; angle += 10) {
		field->_enemyMissile.push_back(new SteadyMissileF(
		    trival_missile_path, _rect.center().x() + 10 * cos(angle),
		    _rect.center().y() + 10 * sin(angle), 3 * cos(angle), 3 * sin(angle), 50));
	}
	if (++counter >= 5) {
		counter = 0, timer = 0;
		_shoot_state = 0;
	}
}

void BossEnemyPlane::updatePosition() {
	if (_rect.y() <= battlefield_border.y() + 100) {
		moveBy(0, 10);
	}
}

void BossEnemyPlane::shootMissiles(BattleField* field) {
	switch (_shoot_state) {
		case 0: _shoot_state = with_probability(0.5) ? 0 : randint(1, 3); break;
		case 1: shootMissilesAround(field); break;
		case 2: shootMissilesArc(field); break;
	}
}

void BossEnemyPlane::afterDeath(BattleField* field) {
	return;
}

void BossEnemyPlane::drawOn(QPainter& painter) {
	_Plane::drawOn(painter);
	painter.drawRect(QRect(_rect.x(), _rect.y() - 3, _rect.width(), 3));
	painter.fillRect(QRect(_rect.x(), _rect.y() - 3, _rect.width(), 3), Qt::red);
	painter.fillRect(
	    QRect(_rect.x(), _rect.y() - 3, _rect.width() * 1.0 * _health / _max_health, 3), Qt::green);
}

bool BossEnemyPlane::out() const {
	return false;
}