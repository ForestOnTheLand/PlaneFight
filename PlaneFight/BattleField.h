#pragma once

#include "util.h"
#include "ui_BattleField.h"
#include "EnemyPlane.h"
#include "ExplosionEffect.h"
#include "Generator.h"
#include "Menu.h"

QT_BEGIN_NAMESPACE
namespace Ui {
	class BattleFieldClass;
};
QT_END_NAMESPACE

class EnemyPlane;
class Menu;

class BattleField : public QWidget {
	Q_OBJECT

private:
	QTimer* _timer;
	Ui::BattleFieldClass* ui;
	KeyState _key;
	EnemyGenerator* _generator;
	Menu* mainMenu;

public:
	BattleField(QWidget* parent = nullptr, Menu* menu = nullptr);
	~BattleField();

public:
	void start(int level = 1);
	void updateAll();
	void gameOver();
	void gameWin();

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
	QPixmap pic1, pic2;
	std::vector<_EnemyPlane*> enemy_planes;
	std::vector<_Effect*> effects;
	std::vector<_Missile*> enemy_missiles;
	std::vector<_Bonus*> drops;
	void paintEvent(QPaintEvent* _event) final;
	void mouseMoveEvent(QMouseEvent* _event) final;
	void keyPressEvent(QKeyEvent* _event) final;
	void keyReleaseEvent(QKeyEvent* _event) final;

	friend class MessageDisplay;
	friend class PlayerPlane;
};
