#include "Rule.h"

Rule::Rule(QWidget *parent,Menu* menu)
	: QWidget(parent)
	, ui(new Ui::RuleClass()),mainMenu(menu)
{
	ui->setupUi(this);

	QString exit_button_style = "QPushButton{background-color:grey;\
										color: white; border-radius:10px ; border : 2px groove gray;\
										border-style: outset;}"
		"QPushButton:hover{background-color: white;color: black;}"
		"QPushButton:pressed{background-color:rgb{85,170,255};\
									border-style: inset;}";

	ui->Return_bt->setStyleSheet(exit_button_style);
	connect(ui->Return_bt, &QPushButton::clicked, this, &Rule::Return);

	ui->textBrowser->resize(760, 700);

	setAutoFillBackground(true);
	QImage image;
	QPalette palette;
	image.load(":/PlaneFight/img/rule.jpg");
	palette.setBrush(this->backgroundRole(), QBrush(image));
	setPalette(palette);
}

void Rule::Return() {
	setWindowTitle("choose your mode");
	mainMenu->stackWidget->setCurrentIndex(0);

}

Rule::~Rule()
{
	delete ui;
}
