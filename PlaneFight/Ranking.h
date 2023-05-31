#pragma once

#include <QWidget>
#include "ui_Ranking.h"
#include <vector>
#include "Menu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class RankingClass; };
QT_END_NAMESPACE

class Ranking : public QWidget
{
	Q_OBJECT

public:
	Ranking(QWidget *parent = nullptr,Menu* menu=nullptr);
	~Ranking();
	Menu* mainMenu;
	void refill();

public slots:
	void Exit();

private:
	Ui::RankingClass *ui;
};
