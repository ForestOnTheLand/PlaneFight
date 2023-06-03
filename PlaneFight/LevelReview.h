#pragma once

#include <QWidget>
#include "ui_LevelReview.h"
#include "Menu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LevelReviewClass; };
QT_END_NAMESPACE

class LevelReview : public QWidget
{
	Q_OBJECT

public:
	LevelReview(QWidget *parent = nullptr,Menu* menu=nullptr);
	~LevelReview();
	
public:
	int score=0;
	Menu* mainMenu;
	void refill(int winOrlose=1);

public slots:
	void Return();

private:
	Ui::LevelReviewClass *ui;
};
