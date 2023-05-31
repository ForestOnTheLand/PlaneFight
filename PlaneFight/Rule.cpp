#include "Rule.h"

Rule::Rule(QWidget *parent,Menu* menu)
	: QMainWindow(parent)
	, ui(new Ui::RuleClass()),mainMenu(menu)
{
	ui->setupUi(this);
	connect(ui->exitButton, &QPushButton::clicked, this, &Rule::Exit);
}

void Rule::Exit() {
	mainMenu->stackWidget->setCurrentIndex(0);
}

Rule::~Rule()
{
	delete ui;
}
