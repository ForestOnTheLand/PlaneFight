#include "Ranking.h"
#include<iostream>
#include<stdio.h>

Ranking::Ranking(QWidget *parent,Menu* menu)
	: QWidget(parent)
	, ui(new Ui::RankingClass()),mainMenu(menu)
{
	ui->setupUi(this);
	QString exit_button_style = "QPushButton{background-color:grey;\
										color: white; border-radius:10px ; border : 2px groove gray;\
										border-style: outset;}"
		"QPushButton:hover{background-color: white;color: black;}"
		"QPushButton:pressed{background-color:rgb{85,170,255};\
									border-style: inset;}";

	ui->Return_bt->setStyleSheet(exit_button_style);
	connect(ui->Return_bt, &QPushButton::clicked, this, &Ranking::Exit);

	setAutoFillBackground(true);
	QImage image;
	QPalette palette;
	image.load(":/PlaneFight/img/ranking.jpg");

	palette.setBrush(this->backgroundRole(), QBrush(image));
	setPalette(palette);
}

void Ranking::Exit() {
	mainMenu->stackWidget->setCurrentIndex(1);
}

struct Data_RK {
	std::string day = "";
	std::string time = "";
	int score = 0;
}history_RK[7];

void Ranking::refill() {
	freopen("DataRecord.txt", "r", stdin);
	for (int i = 0; i < 5; ++i) {
		std::cin >> history_RK[i].day >> history_RK[i].time >> history_RK[i].score;
	}
	fclose(stdin);
	ui->first_t->setText(tr(history_RK[0].day.c_str()) + tr(" ") + tr(history_RK[0].time.c_str()));
	ui->first_s->setText(QString::number(history_RK[0].score));
	ui->second_t_2->setText(tr(history_RK[1].day.c_str()) + tr(" ") + tr(history_RK[1].time.c_str()));
	ui->second_s_2->setText(QString::number(history_RK[1].score));
	ui->third_t_2->setText(tr(history_RK[2].day.c_str()) + tr(" ") + tr(history_RK[2].time.c_str()));
	ui->third_s_2->setText(QString::number(history_RK[2].score));
	ui->fourth_t->setText(tr(history_RK[3].day.c_str()) + tr(" ") + tr(history_RK[3].time.c_str()));
	ui->fourth_s->setText(QString::number(history_RK[3].score));
	ui->fifth_t->setText(tr(history_RK[4].day.c_str()) + tr(" ") + tr(history_RK[4].time.c_str()));
	ui->fifth_s->setText(QString::number(history_RK[4].score));
}

Ranking::~Ranking()
{
	delete ui;
}
