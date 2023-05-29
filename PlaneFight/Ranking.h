#pragma once

#include <QWidget>
#include "ui_Ranking.h"
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class RankingClass; };
QT_END_NAMESPACE

class Ranking : public QWidget
{
	Q_OBJECT

public:
	Ranking(QWidget *parent = nullptr);
	~Ranking();
	 

private:
	Ui::RankingClass *ui;
};
