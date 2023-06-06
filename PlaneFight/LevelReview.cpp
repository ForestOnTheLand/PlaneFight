#include "LevelReview.h"
#include "iostream"
#include "cmath"
#include "algorithm"

LevelReview::LevelReview(QWidget* parent, Menu* menu)
    : QWidget(parent), ui(new Ui::LevelReviewClass()), mainMenu(menu) {
	ui->setupUi(this);
	QString exit_button_style = "QPushButton{background-color:grey;\
										color: white; border-radius:10px ; border : 2px groove gray;\
										border-style: outset;}"
	                            "QPushButton:hover{background-color: white;color: black;}"
	                            "QPushButton:pressed{background-color:rgb{85,170,255};\
									border-style: inset;}";
	ui->Return_bt->setStyleSheet(exit_button_style);
	connect(ui->Return_bt, &QPushButton::clicked, this, &LevelReview::Return);

	setAutoFillBackground(true);
	QImage image;
	QPalette palette;
	image.load(":/PlaneFight/img/review.jpg");
	palette.setBrush(this->backgroundRole(), QBrush(image));
	setPalette(palette);

}

void LevelReview::refill(int win) {
	ui->score->setText(QString::number(score));
	if (win) {
		ui->Title->setCurrentIndex(0);
		ui->score_label->setStyleSheet("color:#ff0000");
		ui->score->setStyleSheet("color:#ff0000");
		ui->rating_label->setStyleSheet("color:#ff0000");
		ui->stackedWidget_3->setCurrentIndex(score > 0 ? 1 : 0);
		ui->stackedWidget_2->setCurrentIndex(score >= 5000 ? 1 : 0);
		ui->stackedWidget->setCurrentIndex(score >= 9000 ? 1 : 0);
		int star[4] = {0};
		freopen("levelPRdata.txt", "r", stdin);
		std::cin >> star[1] >> star[2] >> star[3];
		fclose(stdin);
		freopen("levelPRdata.txt", "w", stdout);
		if (score >= 9000) {
			star[mainMenu->mode] = 3;
		} else if (score >= 7000) {
			star[mainMenu->mode] = std::max(star[mainMenu->mode], 2);
		} else {
			star[mainMenu->mode] = std::max(star[mainMenu->mode], 1);
		}
		for (int i = 1; i <= 3; ++i) {
			std::cout << star[i] << '\n';
		}
		fclose(stdout);
	} else {
		ui->Title->setCurrentIndex(1);
		ui->score_label->setStyleSheet("color:#0000ff");
		ui->score->setStyleSheet("color:#0000ff");
		ui->rating_label->setStyleSheet("color:#0000ff");
		ui->stackedWidget->setCurrentIndex(0);
		ui->stackedWidget_2->setCurrentIndex(0);
		ui->stackedWidget_3->setCurrentIndex(0);
	}
}

void LevelReview::Return() {
	mainMenu->stackWidget->setCurrentIndex(1);
	setWindowTitle("choose your mode");
}

LevelReview::~LevelReview() {
	delete ui;
}
