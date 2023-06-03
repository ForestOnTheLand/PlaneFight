#include "BossEnemyPlane.h"
#include "BattleField.h"
#include "SteadyMissile.h"
#include "TrackMissile.h"
#include "TargetEffect.h"
#include "Generator.h"
#include "EnemyPlane.h"
#include "util.h"
#include "Laser.h"
#define _MATH_DEFINES_DEFINED

static constexpr const char* around_missile_path = ":/PlaneFight/img/bullet/flame_bullet_red_1.png";
static constexpr const char* round_missile_path = ":/PlaneFight/img/bullet/orb_bullet_orange.png";
static constexpr const char* arc_missile_path = ":/PlaneFight/img/bullet/star_bullet_purple.png";
static constexpr const char* knife_down_missile_path = ":/PlaneFight/img/bullet/etama6_4_down.png";
static constexpr const char* knife_right_missile_path = ":/PlaneFight/img/bullet/etama6_4_right.png";
static constexpr const char* big_missile_path = ":/PlaneFight/img/bullet/big_bullet_blue.png";


BossEnemyPlane::BossEnemyPlane(const char* __image_path, int __health, int __attack)
    : _EnemyPlane(__image_path, __health, {battlefield_border.center().x(), 0}),
      _max_health(_health), _attack(__attack) {}

void BossEnemyPlane::shootMissilesAround(BattleField* field) {
	static double angle = 0;
	static int timer = 0;
	if (++timer <= 3)
		return;
	angle += 7, timer = 0;
	field->enemy_missiles.push_back(new SteadyMissileF(
	    around_missile_path, _rect.center().x() + 10 * cos(angle),
	    _rect.center().y() + 10 * sin(angle), 2 * cos(angle), 2 * sin(angle), _attack));
	if (angle > 720) {
		angle = 0, timer = 0;
		_shoot_state = 0;
	}
}


void BossEnemyPlane::shootMissilesRound(BattleField* field) {
	static int counter = 0;
	static int timer = 0;
	if (++timer <= 10)
		return;
	timer = 0;
	for (double angle = 0; angle < 2 * M_PI; angle += M_PI / 20) {
		field->enemy_missiles.push_back(new SteadyMissileF(
		    round_missile_path, _rect.center().x() + 10 * cos(angle),
		    _rect.center().y() + 10 * sin(angle), 3 * cos(angle), 3 * sin(angle), _attack));
	}
	if (++counter >= 5) {
		counter = 0, timer = 0;
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
		field->enemy_missiles.push_back(new SteadyMissileF(
		    arc_missile_path, _rect.center().x() + 10 * cos(angle),
		    _rect.center().y() + 10 * sin(angle), 3 * cos(angle), 3 * sin(angle), _attack));
	}
	if (++counter >= 5) {
		counter = 0, timer = 0;
		_shoot_state = 0;
	}
}

void BossEnemyPlane::shootLaser(BattleField* field) {
	_laser.src = _rect.center();
	if ((_laser.theta += 0.01) > 2 * M_PI) {
		_shoot_state = 0;
		_laser.theta = 0;
		return;
	}
}

void BossEnemyPlane::shootMissilesTrack(BattleField* field) {
	static int counter = 0;
	static int timer = 0;
	if (++timer <= 10)
		return;
	timer = 0;
	for (double angle = 0; angle <= M_PI; angle += M_PI / 10) {
		field->enemy_missiles.push_back(new TrackMissile(
		    round_missile_path, _rect.center().x() + 10 * cos(angle),
		    _rect.center().y() + 10 * sin(angle), 3 * cos(angle), 3 * sin(angle), _attack,30));
	}
	if (++counter >= 3) {
		counter = 0, timer = 0;
		_shoot_state = 0;
	}
}

void BossEnemyPlane::shootMissilesTarget(BattleField* field) {
	static int counter = 0;
	static int timer = 0;
	static int x = 0;
	static int y = 0;
	if (++timer <= 10)
		return;
	timer = 0;
	if (counter == 0) {
		x = randint(100, 400);
		y = randint(100, 600);
		field->effects.push_back(new TargetEffect(QPoint(x, y)));
	}
	if (counter == 1) {
		field->enemy_missiles.push_back(new TrackMissile(
			big_missile_path, x, y, 0, 3, 50, 0));
	}
	if (++counter >= 2) {
		counter = 0, timer = 0;
		x = 0, y = 0;
		_shoot_state = 0;
	}
}

void BossEnemyPlane::shootMissilesCrossing(BattleField* field) {
	static int counter = 0;
	static int timer = 0;
	if (++timer <= 50)
		return;
	timer = 0;
	for (int i = 0; i <= 500; i += 50) {
		field->enemy_missiles.push_back(new SteadyMissile(
			knife_down_missile_path, i, 50, 0, 1, 50));
	}
	for (int i = 0; i <= 700; i += 50) {
		field->enemy_missiles.push_back(new SteadyMissile(
			knife_right_missile_path, 50, i, 1, 0, 50));
	}
	if (++counter >= 10) {
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
		case 0: _shoot_state = with_probability(0.5) ? 0 : randint(1, 8); break;
		case 1: shootMissilesAround(field); break;
		case 2: shootMissilesArc(field); break;
		case 3: shootMissilesRound(field); break;
		case 4: shootLaser(field); break;
		case 5: shootMissilesTrack(field); break;
		case 6: shootMissilesCrossing(field); break;
		case 7: shootMissilesTarget(field); break;
	}
}

void BossEnemyPlane::afterDeath(BattleField* field) {
	field->effects.push_back(new ExplosionEffect(_rect.topLeft()));
	field->effects.push_back(new ExplosionEffect(_rect.bottomRight()));
	return;
}

void BossEnemyPlane::drawOn(QPainter& painter) {
	_Plane::drawOn(painter);
	painter.drawRect(QRect(_rect.x(), _rect.y() - 3, _rect.width(), 3));
	painter.fillRect(QRect(_rect.x(), _rect.y() - 3, _rect.width(), 3), Qt::red);
	painter.fillRect(
	    QRect(_rect.x(), _rect.y() - 3, _rect.width() * 1.0 * _health / _max_health, 3), Qt::green);
	if (_shoot_state == 4)
		_laser.drawOn(painter);
}

bool BossEnemyPlane::out() const {
	return false;
}

void BossEnemyPlane::hurt(_Plane* plane) {
	_Plane::hurt(plane);
	if (_shoot_state == 4) {
		_laser.hurt();
	}
}
