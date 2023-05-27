#pragma once

#include "util.h"
#include "ui_BattleField.h"
#include "EnemyPlane.h"
#include "ExplosionEffect.h"
#include "Generator.h"

QT_BEGIN_NAMESPACE
namespace Ui {
	class BattleFieldClass;
};
QT_END_NAMESPACE

class EnemyPlane;

class BattleField : public QWidget {
	Q_OBJECT

private:
	QTimer* _timer;
	Ui::BattleFieldClass* ui;
	KeyState _key;
	EnemyGenerator* _generator;

public:
	BattleField(QWidget* parent = nullptr);
	~BattleField();

public:
	void start();
	void updateAll();
	void gameOver();

private:
	void generateEnemy();
	void checkDeadPlane();
	void checkCollision();
	void paintEffect(QPainter& painter);
	void processKeyEvent();
	void updateMissiles();
	void updateDrops();
	void pause();

public:
	std::vector<_EnemyPlane*> _enemies;
	std::vector<_Effect*> _effects;
	std::vector<_Missile*> _enemyMissile;
	std::vector<_Bonus*> _drops;
	void paintEvent(QPaintEvent* _event) final;
	void mouseMoveEvent(QMouseEvent* _event) final;
	void keyPressEvent(QKeyEvent* _event) final;
	void keyReleaseEvent(QKeyEvent* _event) final;
};
