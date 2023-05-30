#include "Menu.h"
#include "ui_Menu.h"
#include "BattleField.h"
#include "qpushbutton.h"
#include "qpainter.h"
#include "qpixmap.h"
#include "qpoint.h"
#include "GameReview.h"
#include "Ranking.h"
#include "BackgroundMusic.h"

Menu::Menu(QWidget* parent) : QWidget(parent), ui(new Ui::MenuClass) {
	BackgroundMusic::load(":/PlaneFight/sound/lockdown.wav");
	BackgroundMusic::play();

	ui->setupUi(this);

	stackWidget = new QStackedWidget();
	gameWidgets.push_back(new QWidget());                     // 0 interface for start menu
	gameWidgets.push_back(new QWidget());                     // 1 interface for choosing mode
	gameWidgets.push_back(new BattleField(nullptr, this));    // 2 interface for survive mode
	gameWidgets.push_back(new QWidget());                     // 3 interface for choosing level mode
	gameWidgets.push_back(new Ranking(nullptr));              // 4 interface for ranking
	gameWidgets.push_back(new GameReview(nullptr));           // 5 interface for game review
	gameWidgets.push_back(new QWidget());                     // 6 interface for rule
	gameWidgets.push_back(new QWidget());                     // 7 interface for levels
	gameWidgets.push_back(new QWidget());                     // 8 interface for levels

	for (int i = 0; i <= 1; i++) {
		gameWidgets[i]->setAutoFillBackground(true);
		QImage image;
		QPalette palette;
		image.load(":/PlaneFight/img/MenuBackground1.png");
		palette.setBrush(this->backgroundRole(), QBrush(image));
		gameWidgets[i]->setPalette(palette);
	}

	for (int i = 0; i < 3; ++i) {
		startButtons.push_back(new QPushButton(gameWidgets[0]));
		switch (i) {
			case 0:
				startButtons[i]->setText("Start Now!");
				startButtons[i]->setFont(QFont("consolas", 17));
				startButtons[i]->setGeometry(QRect(270, 200, 191, 71));
				connect(startButtons[i], &QPushButton::clicked, this, &Menu::StartGame);
				break;
			case 1:
				startButtons[i]->setText("Rules");
				startButtons[i]->setFont(QFont("consolas", 17));
				startButtons[i]->setGeometry(QRect(270, 400, 191, 71));
				connect(startButtons[i], &QPushButton::clicked, this, &Menu::ShowRules);
				break;
			case 2:
				startButtons[i]->setText("Leave");
				startButtons[i]->setFont(QFont("consolas", 17));
				startButtons[i]->setGeometry(QRect(270, 600, 191, 71));
				connect(startButtons[i], &QPushButton::clicked, this, &Menu::Leave);
				break;
			default: startButtons[i]->setText("bt"); break;
		}
	}

	for (int i = 0; i < 3; ++i) {
		gameModes.push_back(new QPushButton(gameWidgets[1]));
		switch (i) {
			case 0:
				gameModes[i]->setText("Survive Mode");
				gameModes[i]->setFont(QFont("consolas", 17));
				gameModes[i]->setGeometry(QRect(270, 200, 191, 71));
				connect(gameModes[i], &QPushButton::clicked, this, &Menu::GameMode1);
				break;
			case 1:
				gameModes[i]->setText("level Mode");
				gameModes[i]->setFont(QFont("consolas", 17));
				gameModes[i]->setGeometry(QRect(270, 400, 191, 71));
				connect(gameModes[i], &QPushButton::clicked, this, &Menu::GameMode2);
				break;
			case 2:
				gameModes[i]->setText("Rankings");
				gameModes[i]->setFont(QFont("consolas", 17));
				gameModes[i]->setGeometry(QRect(270, 600, 191, 71));
				connect(gameModes[i], &QPushButton::clicked, this, &Menu::GameMode3);
				break;
			default: gameModes[i]->setText("bt"); break;
		}
		// menuButtonLayout.addWidget(gameModes[i]);
	}
	// gameWidgets[0]->setLayout(&menuButtonLayout);

	for (int i = 0; i < 9; ++i) {
		stackWidget->addWidget(gameWidgets[i]);
	}

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
	setWindowTitle("Rankings");
	stackWidget->setCurrentIndex(4);
}

Menu::~Menu() {
	for (auto iter = gameModes.begin(); iter != gameModes.end(); ++iter) {
		if (*iter) {
			delete *iter;
		}
	}
	for (auto iter = startButtons.begin(); iter != startButtons.end(); ++iter) {
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
