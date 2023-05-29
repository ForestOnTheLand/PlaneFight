#pragma once

#include <QWidget>
#include "ui_GameReview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GameReviewClass; };
QT_END_NAMESPACE

class GameReview : public QWidget
{
	Q_OBJECT

public:
	GameReview(QWidget *parent = nullptr);
	~GameReview();
	int score;
	void refill();

private:
	Ui::GameReviewClass *ui;
};
