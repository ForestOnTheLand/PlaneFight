#include "Ranking.h"

Ranking::Ranking(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::RankingClass())
{
	ui->setupUi(this);
}

Ranking::~Ranking()
{
	delete ui;
}
