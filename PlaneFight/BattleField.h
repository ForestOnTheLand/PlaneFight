#pragma once

#include "util.h"
#include <QWidget>
#include <qtimer.h>
#include <qpainter.h>
#include <qevent.h>
#include "ui_BattleField.h"
#include "EnemyPlane.h"
#include "ExplosionEffect.h"
#include "_Missile.h"
#include <vector>

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
	std::vector<EnemyPlane*> _enemies;
	std::vector<_Effect*> _effects;
	KeyState _key;

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

public:
	std::vector<_Missile*> _enemyMissile;
	std::vector<_Missile*> _enemyDrop;
	void paintEvent(QPaintEvent* _event) final;
	void mouseMoveEvent(QMouseEvent* _event) final;
	void keyPressEvent(QKeyEvent* _event) final;
	void keyReleaseEvent(QKeyEvent* _event) final;
};
