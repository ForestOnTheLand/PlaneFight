#pragma once

#include <QWidget>
#include "ui_Rule.h"
#include "Menu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class RuleClass; };
QT_END_NAMESPACE

class Rule : public QWidget
{
	Q_OBJECT

public:
	Rule(QWidget *parent = nullptr,Menu* manu=nullptr);
	~Rule();

public:
	Menu* mainMenu;

public slots:
	void Return();

private:
	Ui::RuleClass *ui;
};
