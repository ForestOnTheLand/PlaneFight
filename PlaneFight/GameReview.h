#pragma once

#include <QWidget>
#include "ui_GameReview.h"
#include "Menu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GameReviewClass; };
QT_END_NAMESPACE

class GameReview : public QWidget
{
	Q_OBJECT

public:
	GameReview(QWidget *parent = nullptr,Menu* menu=nullptr);
	~GameReview();
	int score;
	void refill();
	Menu* mainMenu;

public slots:
	void Return();

private:
	Ui::GameReviewClass *ui;
};
