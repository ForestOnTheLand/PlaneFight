#include "Rule.h"

Rule::Rule(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::RuleClass())
{
	ui->setupUi(this);
}

Rule::~Rule()
{
	delete ui;
}
