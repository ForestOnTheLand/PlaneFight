#include "GameReview.h"
#include <algorithm>
#include <string>
#include <stdio.h>
#include <iostream>
#include <ctime>
#include "Menu.h"

struct Data_GR {
	std::string day="";
	std::string time="";
	std::int32_t score=0;
	bool operator<(const Data_GR& obj2) const{
		return score > obj2.score;
	}
}history[7];

GameReview::GameReview(QWidget *parent,Menu* menu)
	: QWidget(parent)
	, ui(new Ui::GameReviewClass()),score(0),mainMenu(menu)
{
	ui->setupUi(this);
	connect(ui->commandLinkButton, &QPushButton::clicked, this, &GameReview::Return);
}

void GameReview::Return() {
	mainMenu->stackWidget->setCurrentIndex(1);
}

void GameReview::refill() {
	ui->gameScore->setText(QString::number(score));
	if (score >= 9000) {
		ui->rating->setText(tr("SSS"));
	}
	else if (score >= 8000) {
		ui->rating->setText(tr("SS"));
	}
	else if (score >= 7000) {
		ui->rating->setText(tr("S"));
	}
	else if (score >= 6000) {
		ui->rating->setText(tr("A"));
	}
	else if (score >= 5000) {
		ui->rating->setText(tr("B"));
	}
	else {
		ui->rating->setText(tr("C"));
	}
	freopen("DataRecord.txt", "r", stdin);
	for (int i = 0; i < 5; ++i) {
		std::cin >> history[i].day >> history[i].time >> history[i].score;
	}
	std::fclose(stdin);
	std::sort(history, history + 5);
	if (score > history[4].score) {
		ui->newRecord_icon->setCurrentIndex(1);
		time_t now = time(nullptr);
		tm* tm_t = localtime(&now);
		int month = tm_t->tm_mon + 1;
		int day = tm_t->tm_mday;
		int hour = tm_t->tm_hour;
		int min = tm_t->tm_min;
		freopen("DataRecord.txt", "w", stdout);
		int cnt = 0;
		bool flag = 0;
		for (int i = 0; i < 5; ++i) {
			if (cnt == 5) {
				break;
			}
			if (history[i].score >= score||flag==1) {
				std::cout << history[i].day << '\n';
				std::cout << history[i].time << '\n';
				std::cout << history[i].score << '\n';
				//flag = 1;
				cnt++;
			}
			else {
				std::printf("%02d/%02d\n", month, day);
				std::printf("%02d:%02d\n", hour, min);
				std::printf("%d\n", score);
				flag = 1;
				cnt++;
				i--;
			}
		}
		fclose(stdout);
	}
	else {
		ui->newRecord_icon->setCurrentIndex(1);
	}
}

GameReview::~GameReview()
{
	delete ui;
}
