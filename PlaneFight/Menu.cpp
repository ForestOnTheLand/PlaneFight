#include "Menu.h"
#include "ui_Menu.h"
#include "BattleField.h"
#include "qpushbutton.h"

Menu::Menu(QWidget* parent) : QWidget(parent), ui(new Ui::MenuClass) {
	ui->setupUi(this);

	stackWidget = new QStackedWidget();
	gameWidgets[0] = new QWidget();        // interface for menu
	gameWidgets[1] = new BattleField();    // interface for battlefield

	for (int i = 0; i < 3; ++i) {
		gameModes[i] = new QPushButton(gameWidgets[0]);
		switch (i) {
			case 0:
				gameModes[i]->setText("Survive Mode");
				gameModes[i]->setFont(QFont("consolas", 17));
				gameModes[i]->setGeometry(QRect(270, 200, 191, 71));
				connect(gameModes[i], &QPushButton::clicked, this, &Menu::GameMode1);
				break;
			case 1:
				gameModes[i]->setText("Story Mode");
				gameModes[i]->setFont(QFont("consolas", 17));
				gameModes[i]->setGeometry(QRect(270, 400, 191, 71));
				connect(gameModes[i], &QPushButton::clicked, this, &Menu::GameMode2);
				break;
			case 2:
				gameModes[i]->setText("Practice Mode");
				gameModes[i]->setFont(QFont("consolas", 17));
				gameModes[i]->setGeometry(QRect(270, 600, 191, 71));
				connect(gameModes[i], &QPushButton::clicked, this, &Menu::GameMode3);
				break;
			default: gameModes[i]->setText("bt"); break;
		}
		// menuButtonLayout.addWidget(gameModes[i]);
	}
	// gameWidgets[0]->setLayout(&menuButtonLayout);

	for (int i = 2; i < 4; ++i) {
		gameWidgets[i] = new QWidget();
	}
	for (int i = 0; i < 4; ++i) {
		stackWidget->addWidget(gameWidgets[i]);
	}

	mainLayout.addWidget(stackWidget);
	setLayout(&mainLayout);
}

void Menu::GameMode1() {
	setWindowTitle("Survive Mode");
	BattleField* game = qobject_cast<BattleField*>(gameWidgets[1]);
	game->start();
	stackWidget->setCurrentIndex(1);
}

void Menu::GameMode2() {
	setWindowTitle("Story Mode");
	stackWidget->setCurrentIndex(2);
}

void Menu::GameMode3() {
	setWindowTitle("Practice Mode");
	stackWidget->setCurrentIndex(3);
}

Menu::~Menu() {
	for (int i = 0; i < 3; ++i) {
		if (gameModes[i]) {
			delete gameModes[i];
		}
	}
	for (int i = 0; i < 4; ++i) {
		if (gameWidgets[i]) {
			delete gameWidgets[i];
		}
	}
	delete stackWidget;
	delete ui;
}
