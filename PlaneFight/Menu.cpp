#include "Menu.h"
#include "ui_Menu.h"
#include "BattleField.h"
#include "qpushbutton.h"
#include "qpainter.h"
#include "qpixmap.h"
#include "qpoint.h"
#include "GameReview.h"
//#include "Rule.h"
#include "Ranking.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <qevent.h>
#include "BackgroundMusic.h"
#include <QDebug>

Menu::Menu(QWidget* parent) : QWidget(parent), ui(new Ui::MenuClass) {
	BackgroundMusic::load(":/PlaneFight/sound/lockdown.wav");
	BackgroundMusic::play();

	ui->setupUi(this);

	stackWidget = new QStackedWidget();
	gameWidgets.push_back(new QWidget());				       //0 interface for start menu
	gameWidgets.push_back(new QWidget());				       //1 interface for choosing mode
	gameWidgets.push_back(new BattleField(nullptr, this));     //2 interface for survive mode
	gameWidgets.push_back(new QWidget());			           //3 interface for choosing level mode
	gameWidgets.push_back(new Ranking(nullptr,this));		   //4 interface for ranking
	gameWidgets.push_back(new GameReview(nullptr, this));	   //5 interface for game review
	gameWidgets.push_back(new QWidget());					   //6 interface for rule
	gameWidgets.push_back(new QWidget());					   //7 interface for levels
	gameWidgets.push_back(new QWidget());					   //8 interface for levels

	for (int i = 0; i <= 1; i++) {
		gameWidgets[i]->setAutoFillBackground(true);
		QImage image;
		QPalette palette;
		image.load(":/PlaneFight/img/MenuBackground1.png");
		palette.setBrush(this->backgroundRole(), QBrush(image));
		gameWidgets[i]->setPalette(palette);
	}

	QString button_style = "QPushButton{background-color:#000000;\
										color: white; border-radius:10px ; border : 2px groove gray;\
										border-style: outset;}"
							"QPushButton:hover{background-color: white;color: black;}"
							"QPushButton:pressed{background-color:rgb{85,170,255};\
									border-style: inset;}";
	
	QString exit_button_style = "QPushButton{background-color:grey;\
										color: white; border-radius:10px ; border : 2px groove gray;\
										border-style: outset;}"
								"QPushButton:hover{background-color: white;color: black;}"
								"QPushButton:pressed{background-color:rgb{85,170,255};\
									border-style: inset;}";

	Title = new QLabel(gameWidgets[0]);
	Title->setText("Plane Fight");
	Title->setFont(QFont("Segoe Print", 48));
	Title->setGeometry(QRect(200, 100, 400, 150));
	Title->setStyleSheet("color:#ff0000");

	for (int i = 0; i < 3; ++i) {
		startButtons.push_back(new QPushButton(gameWidgets[0]));
		startLabels.push_back(new QLabel(gameWidgets[0]));
		startButtons[i]->setMouseTracking(true);
		startLabels[i]->setText("");
		startButtons[i]->setFont(QFont("MV Boli", 20));
		startButtons[i]->setStyleSheet(button_style);

		switch (i) {
			case 0:
				startButtons[i]->setText("Start Now!");
				startButtons[i]->setGeometry(QRect(280, 320, 191, 71));
				startLabels[i]->setGeometry(QRect(210, 320, 65, 71));
				connect(startButtons[i], &QPushButton::clicked, this, &Menu::StartGame);
				break;
			case 1:
				startButtons[i]->setText("Rules");
				startButtons[i]->setGeometry(QRect(280, 450, 191, 71));
				startLabels[i]->setGeometry(QRect(210, 450, 65, 71));
				connect(startButtons[i], &QPushButton::clicked, this, &Menu::ShowRules);
				break;
			case 2:
				startButtons[i]->setText("Leave");
				startButtons[i]->setGeometry(QRect(280, 580, 191, 71));
				startLabels[i]->setGeometry(QRect(210, 580, 65, 71));
				connect(startButtons[i], &QPushButton::clicked, this, &Menu::Leave);
				break;
			default: startButtons[i]->setText("bt"); break;
		}
	}

	toFirstPage = new QPushButton(gameWidgets[1]);
	toFirstPage->setText("<<Return");
	toFirstPage->setFont(QFont("MV Boli", 15));
	toFirstPage->setGeometry(QRect(50, 700, 100, 50));
	toFirstPage->setAutoFillBackground(true);
	toFirstPage->setStyleSheet(exit_button_style);
	connect(toFirstPage, &QPushButton::clicked, this, &Menu::ToFirstPage);

	for (int i = 0; i < 3; ++i) {
		gameModes.push_back(new QPushButton(gameWidgets[1]));
		modeLabels.push_back(new QLabel(gameWidgets[1]));
		gameModes[i]->setFont(QFont("MV Boli", 20));
		gameModes[i]->setMouseTracking(true);
		gameModes[i]->setStyleSheet(button_style);
		modeLabels[i]->setText("");
		switch (i) {
			case 0:
				gameModes[i]->setText("Survive Mode");
				gameModes[i]->setGeometry(QRect(290, 200, 191, 71));
				modeLabels[i]->setGeometry(QRect(220, 200, 65, 71));
				connect(gameModes[i], &QPushButton::clicked, this, &Menu::GameMode1);
				break;
			case 1:
				gameModes[i]->setText("level Mode");
				gameModes[i]->setGeometry(QRect(290, 400, 191, 71));
				modeLabels[i]->setGeometry(QRect(220, 400, 65, 71));
				connect(gameModes[i], &QPushButton::clicked, this, &Menu::GameMode2);
				break;
			case 2:
				gameModes[i]->setText("Rankings");
				gameModes[i]->setGeometry(QRect(290, 600, 191, 71));
				modeLabels[i]->setGeometry(QRect(220, 600, 65, 71));
				connect(gameModes[i], &QPushButton::clicked, this, &Menu::GameMode3);
				break;
			default: gameModes[i]->setText("bt"); break;
		}
		// menuButtonLayout.addWidget(gameModes[i]);
	}
	// gameWidgets[0]->setLayout(&menuButtonLayout);

	for (int i = 0; i < 9; ++i) {
		stackWidget->addWidget(gameWidgets[i]);
		gameWidgets[i]->setMouseTracking(true);
	}
	stackWidget->setMouseTracking(true);
	mainLayout.addWidget(stackWidget);
	setLayout(&mainLayout);
}

void Menu::StartGame() {
	setWindowTitle("choose your mode");
	stackWidget->setCurrentIndex(1);
}

void Menu::Leave() {
	exit(0);
}

void Menu::ShowRules() {
	setWindowTitle("rules");
	stackWidget->setCurrentIndex(6);
}

void Menu::GameMode1() {
	setWindowTitle("Survive Mode");
	BattleField* game = qobject_cast<BattleField*>(gameWidgets[2]);
	game->start();
	stackWidget->setCurrentIndex(2);
}

void Menu::GameMode2() {
	setWindowTitle("level Mode");
	stackWidget->setCurrentIndex(3);
}


void Menu::GameMode3() {
	Ranking* pRanking = qobject_cast<Ranking*>(gameWidgets[4]);
	pRanking->refill();
	setWindowTitle("Rankings");
	stackWidget->setCurrentIndex(4);
}

void Menu::ToFirstPage() {
	stackWidget->setCurrentIndex(0);
}

void Menu::mouseMoveEvent(QMouseEvent* _event) {
	int _x = _event->pos().x(), _y = _event->pos().y();
	if (_x > startButtons[0]->geometry().left() && _x < startButtons[0]->geometry().right() && stackWidget->currentIndex() == 0) {
		if (_y < startButtons[0]->geometry().bottom() && _y > startButtons[0]->geometry().top()) {
			startLabels[0]->setPixmap(QPixmap(QString::fromUtf8(":/PlaneFight/img/planeIcon.svg")));
			startLabels[1]->setPixmap(QPixmap("none"));
			startLabels[2]->setPixmap(QPixmap("none"));
		}
		else if (_y < startButtons[1]->geometry().bottom() && _y > startButtons[1]->geometry().top()) {
			startLabels[0]->setPixmap(QPixmap("none"));
			startLabels[1]->setPixmap(QPixmap(QString::fromUtf8(":/PlaneFight/img/planeIcon.svg")));
			startLabels[2]->setPixmap(QPixmap("none"));
		}
		else if (_y < startButtons[2]->geometry().bottom() && _y > startButtons[2]->geometry().top()) {
			startLabels[0]->setPixmap(QPixmap("none"));
			startLabels[1]->setPixmap(QPixmap("none"));
			startLabels[2]->setPixmap(QPixmap(QString::fromUtf8(":/PlaneFight/img/planeIcon.svg")));
		} else {
			startLabels[0]->setPixmap(QPixmap("none"));
			startLabels[1]->setPixmap(QPixmap("none"));
			startLabels[2]->setPixmap(QPixmap("none"));
		}
	} else if (stackWidget->currentIndex() == 0) {
		startLabels[0]->setPixmap(QPixmap("none"));
		startLabels[1]->setPixmap(QPixmap("none"));
		startLabels[2]->setPixmap(QPixmap("none"));
	}
	if (_x > gameModes[0]->geometry().left() && _x < gameModes[0]->geometry().right() && stackWidget->currentIndex()==1) {
		if (_y < gameModes[0]->geometry().bottom() && _y > gameModes[0]->geometry().top()) {
			modeLabels[0]->setPixmap(QPixmap(QString::fromUtf8(":/PlaneFight/img/planeIcon.svg")));
			modeLabels[1]->setPixmap(QPixmap("none"));
			modeLabels[2]->setPixmap(QPixmap("none"));
		}
		else if (_y < gameModes[1]->geometry().bottom() && _y > gameModes[1]->geometry().top()) {
			modeLabels[0]->setPixmap(QPixmap("none"));
			modeLabels[1]->setPixmap(QPixmap(QString::fromUtf8(":/PlaneFight/img/planeIcon.svg")));
			modeLabels[2]->setPixmap(QPixmap("none"));
		}
		else if (_y < gameModes[2]->geometry().bottom() && _y > gameModes[2]->geometry().top()) {
			modeLabels[0]->setPixmap(QPixmap("none"));
			modeLabels[1]->setPixmap(QPixmap("none"));
			modeLabels[2]->setPixmap(QPixmap(QString::fromUtf8(":/PlaneFight/img/planeIcon.svg")));
		} else {
			modeLabels[0]->setPixmap(QPixmap("none"));
			modeLabels[1]->setPixmap(QPixmap("none"));
			modeLabels[2]->setPixmap(QPixmap("none"));
		}
	} else if (stackWidget->currentIndex() == 1) {
		modeLabels[0]->setPixmap(QPixmap("none"));
		modeLabels[1]->setPixmap(QPixmap("none"));
		modeLabels[2]->setPixmap(QPixmap("none"));
	}
}

Menu::~Menu() {
	if (Title)
		delete Title;
	if (toFirstPage)
		delete toFirstPage;
	for (auto iter = gameModes.begin(); iter != gameModes.end(); ++iter) {
		if (*iter) {
			delete *iter;
		}
	}
	for (auto iter = modeLabels.begin(); iter != modeLabels.end(); ++iter) {
		if (*iter) {
			delete *iter;
		}
	}
	for (auto iter = startButtons.begin(); iter != startButtons.end(); ++iter) {
		if (*iter) {
			delete *iter;
		}
	}
	for (auto iter = startLabels.begin(); iter != startLabels.end(); ++iter) {
		if (*iter) {
			delete *iter;
		}
	}
	for (auto iter = gameWidgets.begin(); iter != gameWidgets.end(); ++iter) {
		if (*iter) {
			delete *iter;
		}
	}
	for (auto iter = to_remove.begin(); iter != to_remove.end(); ++iter) {
		if (*iter) {
			// qDebug() << "called"<<'\n';
			delete *iter;
		}
	}
	delete stackWidget;
	delete ui;
}
