#include "LevelChoose.h"

LevelChoose::LevelChoose(QWidget *parent, Menu* menu)
	: QWidget(parent)
	, ui(new Ui::LevelChooseClass()), mainMenu(menu)
{
	ui->setupUi(this);
	setMouseTracking(true);
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

	ui->info_table->setCurrentIndex(1);
	ui->Level_1->setStyleSheet(button_style);
	ui->Level_1->setMouseTracking(true);
	ui->Level_2->setStyleSheet(button_style);
	ui->Level_2->setMouseTracking(true);
	ui->Level_3->setStyleSheet(button_style);
	ui->Level_3->setMouseTracking(true);
	ui->Return_bt->setStyleSheet(exit_button_style);
	connect(ui->Level_1, &QPushButton::clicked, this, &LevelChoose::Level);
	connect(ui->Level_2, &QPushButton::clicked, this, &LevelChoose::Level);
	connect(ui->Level_3, &QPushButton::clicked, this, &LevelChoose::Level);
	connect(ui->Return_bt, &QPushButton::clicked, this, &LevelChoose::Return);
}

void LevelChoose::Return() {
	mainMenu->stackWidget->setCurrentIndex(1);
}

void LevelChoose::Level() {
	QPushButton* pLevel = qobject_cast<QPushButton*>(sender());
	BattleField* pGame = qobject_cast<BattleField*>(mainMenu->gameWidgets[2]);
	mainMenu->stackWidget->setCurrentIndex(2);
	if (pLevel == ui->Level_1) {
		setWindowTitle("Level_One");
		pGame->start(1);
	}
	else if (pLevel == ui->Level_2) {
		setWindowTitle("Level_Two");
		pGame->start(2);
	}
	else {
		setWindowTitle("Level_Three");
		pGame->start(3);
	}
}

void LevelChoose::mouseMoveEvent(QMouseEvent* _event) {
	int _x = _event->pos().x(), _y = _event->pos().y();
	//qDebug() << "aaa" << '\n';
	if (_x > ui->Level_1->geometry().left() && _x < ui->Level_1->geometry().right()
		&& mainMenu->stackWidget->currentIndex() == 3 &&
		_y < ui->Level_1->geometry().bottom() && _y > ui->Level_1->geometry().top()) {
		ui->info_table->setCurrentIndex(0);
		ui->dr_1->setCurrentIndex(1);
		ui->dr_2->setCurrentIndex(0);
		ui->dr_3->setCurrentIndex(0);
		ui->pr_1->setCurrentIndex(0);
		ui->pr_2->setCurrentIndex(0);
		ui->pr_3->setCurrentIndex(0);
	}
	else if (_x > ui->Level_2->geometry().left() && _x < ui->Level_2->geometry().right()
		&& mainMenu->stackWidget->currentIndex() == 3 &&
		_y < ui->Level_2->geometry().bottom() && _y > ui->Level_2->geometry().top()) {
		ui->info_table->setCurrentIndex(0);
		ui->dr_1->setCurrentIndex(1);
		ui->dr_2->setCurrentIndex(1);
		ui->dr_3->setCurrentIndex(0);
		ui->pr_1->setCurrentIndex(0);
		ui->pr_2->setCurrentIndex(0);
		ui->pr_3->setCurrentIndex(0);
	}
	else if (_x > ui->Level_3->geometry().left() && _x < ui->Level_3->geometry().right()
		&& mainMenu->stackWidget->currentIndex() == 3 &&
		_y < ui->Level_3->geometry().bottom() && _y > ui->Level_3->geometry().top()) {
		ui->info_table->setCurrentIndex(0);
		ui->dr_1->setCurrentIndex(1);
		ui->dr_2->setCurrentIndex(1);
		ui->dr_3->setCurrentIndex(1);
		ui->pr_1->setCurrentIndex(0);
		ui->pr_2->setCurrentIndex(0);
		ui->pr_3->setCurrentIndex(0);
	}
	else if (mainMenu->stackWidget->currentIndex() == 3) {
		ui->info_table->setCurrentIndex(1);
	}
}

LevelChoose::~LevelChoose()
{
	delete ui;
}
