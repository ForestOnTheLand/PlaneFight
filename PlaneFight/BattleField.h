#pragma once

#include <QWidget>
#include <qtimer.h>
#include <qpainter.h>
#include <qevent.h>
#include "ui_BattleField.h"
#include "EnemyPlane.h"
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {
	class BattleFieldClass;
};
QT_END_NAMESPACE

class BattleField : public QWidget {
	Q_OBJECT

private:
	QTimer* _timer;
	Ui::BattleFieldClass* ui;
	std::vector<EnemyPlane*> _enemies;

public:
	BattleField(QWidget* parent = nullptr);
	~BattleField();

public:
	void generateEnemy();
	void start();
	void updateAll();

public:
	void paintEvent(QPaintEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
};
