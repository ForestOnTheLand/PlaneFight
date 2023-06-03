#pragma once

#include <QWidget>
#include "ui_LevelChoose.h"
#include "Menu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LevelChooseClass; };
QT_END_NAMESPACE

class LevelChoose : public QWidget
{
	Q_OBJECT

public:
	LevelChoose(QWidget *parent = nullptr, Menu* menu = nullptr);
	~LevelChoose();
	Menu* mainMenu;

public slots:
	void Level();
	void mouseMoveEvent(QMouseEvent* _event);
	void Return();

private:
	Ui::LevelChooseClass *ui;
};
