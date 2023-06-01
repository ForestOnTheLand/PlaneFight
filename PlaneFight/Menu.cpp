#include "Menu.h"
#include "ui_Menu.h"
#include "BattleField.h"
#include "qpushbutton.h"
#include "qpainter.h"
#include "qpixmap.h"
#include "qpoint.h"
#include "GameReview.h"
#include "Ranking.h"
#include "stdio.h"
#include "iostream"
#include "string"
#include <qevent.h>
#include "BackgroundMusic.h"

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

	Title = new QLabel(gameWidgets[0]);
	Title->setText("Plane Fight");
	Title->setFont(QFont("consolas", 32));
	Title->setGeometry(QRect(250, 100, 400, 150));

	for (int i = 0; i < 3; ++i) {
		startButtons.push_back(new QPushButton(gameWidgets[0]));
		startLabels.push_back(new QLabel(gameWidgets[0]));
		startButtons[i]->setMouseTracking(true);
		startLabels[i]->setText("");
		startButtons[i]->setFont(QFont("consolas", 17));
		startButtons[i]->setAutoFillBackground(true);
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
	toFirstPage->setFont(QFont("consolas", 15));
	toFirstPage->setGeometry(QRect(50, 700, 100, 50));
	toFirstPage->setAutoFillBackground(true);
	connect(toFirstPage, &QPushButton::clicked, this, &Menu::ToFirstPage);

	for (int i = 0; i < 3; ++i) {
		gameModes.push_back(new QCommandLinkButton(gameWidgets[1]));
		modeLabels.push_back(new QLabel(gameWidgets[1]));
		gameModes[i]->setFont(QFont("consolas", 17));
		gameModes[i]->setMouseTracking(true);
		modeLabels[i]->setText("");
		switch (i) {
			case 0:
				gameModes[i]->setText("Survive Mode");
				gameModes[i]->setGeometry(QRect(290, 150, 191, 71));
				gameModes[i]->setIcon(QIcon::fromTheme(tr("none")));
				modeLabels[i]->setGeometry(QRect(220, 140, 65, 71));
				connect(gameModes[i], &QPushButton::clicked, this, &Menu::GameMode1);
				break;
			case 1:
				gameModes[i]->setText(" level Mode");
				gameModes[i]->setGeometry(QRect(290, 350, 191, 71));
				gameModes[i]->setIcon(QIcon::fromTheme(tr("none")));
				modeLabels[i]->setGeometry(QRect(220, 340, 65, 71));
				connect(gameModes[i], &QPushButton::clicked, this, &Menu::GameMode2);
				break;
			case 2:
				gameModes[i]->setText("  Rankings");
				gameModes[i]->setGeometry(QRect(290, 550, 191, 71));
				gameModes[i]->setIcon(QIcon::fromTheme(tr("none")));
				modeLabels[i]->setGeometry(QRect(220, 540, 65, 71));
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
	int _x = _event->globalPos().x(), _y = _event->globalPos().y();
	if (_x > 746 && _x < 935 && stackWidget->currentIndex() == 0) {
		if (_y > 442 && _y < 511) {
			startLabels[0]->setPixmap(QPixmap(QString::fromUtf8(":/PlaneFight/img/planeIcon.svg")));
			startLabels[1]->setPixmap(QPixmap("none"));
			startLabels[2]->setPixmap(QPixmap("none"));
		}
		else if (_y > 573 && _y < 639) {
			startLabels[0]->setPixmap(QPixmap("none"));
			startLabels[1]->setPixmap(QPixmap(QString::fromUtf8(":/PlaneFight/img/planeIcon.svg")));
			startLabels[2]->setPixmap(QPixmap("none"));
		}
		else if (_y > 701 && _y < 771) {
			startLabels[0]->setPixmap(QPixmap("none"));
			startLabels[1]->setPixmap(QPixmap("none"));
			startLabels[2]->setPixmap(QPixmap(QString::fromUtf8(":/PlaneFight/img/planeIcon.svg")));
		}
		else {
			startLabels[0]->setPixmap(QPixmap("none"));
			startLabels[1]->setPixmap(QPixmap("none"));
			startLabels[2]->setPixmap(QPixmap("none"));
		}
	}
	else if(stackWidget->currentIndex() == 0) {
		startLabels[0]->setPixmap(QPixmap("none"));
		startLabels[1]->setPixmap(QPixmap("none"));
		startLabels[2]->setPixmap(QPixmap("none"));
	}
	if (_x > 755 && _x < 945 && stackWidget->currentIndex() == 1) {
		if (_y > 273 && _y < 341) {
			modeLabels[0]->setPixmap(QPixmap(":/PlaneFight/img/planeIcon.svg"));
			modeLabels[1]->setPixmap(QPixmap("none"));
			modeLabels[2]->setPixmap(QPixmap("none"));
		}
		else if (_y > 473 && _y < 541) {
			modeLabels[0]->setPixmap(QPixmap("none"));
			modeLabels[1]->setPixmap(QPixmap(QString::fromUtf8(":/PlaneFight/img/planeIcon.svg")));
			modeLabels[2]->setPixmap(QPixmap("none"));
		}
		else if (_y > 673 && _y < 741) {
			modeLabels[0]->setPixmap(QPixmap("none"));
			modeLabels[1]->setPixmap(QPixmap("none"));
			modeLabels[2]->setPixmap(QPixmap(QString::fromUtf8(":/PlaneFight/img/planeIcon.svg")));
		}
		else {
			modeLabels[0]->setPixmap(QPixmap("none"));
			modeLabels[1]->setPixmap(QPixmap("none"));
			modeLabels[2]->setPixmap(QPixmap("none"));
		}
	}
	else if(stackWidget->currentIndex()==0){
		modeLabels[0]->setPixmap(QPixmap("none"));
		modeLabels[1]->setPixmap(QPixmap("none"));
		modeLabels[2]->setPixmap(QPixmap("none"));
	}

}

Menu::~Menu() {
	if(Title)
		delete Title;
	if (toFirstPage)
		delete toFirstPage;
	for (auto iter = gameModes.begin(); iter!=gameModes.end(); ++iter) {
		if (*iter) {
			delete *iter;
		}
	}
	for (auto iter = modeLabels.begin(); iter != modeLabels.end(); ++iter) {
		if (*iter) {
			delete* iter;
		}
	}
	for (auto iter = startButtons.begin(); iter != startButtons.end(); ++iter) {
		if (*iter) {
			delete *iter;
		}
	}
	for (auto iter = startLabels.begin(); iter != startLabels.end(); ++iter) {
		if (*iter) {
			delete* iter;
		}
	}
	for (auto iter = gameWidgets.begin(); iter != gameWidgets.end();++iter) {
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
