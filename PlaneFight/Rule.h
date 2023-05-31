#pragma once

#include <QMainWindow>
#include "ui_Rule.h"
#include "Menu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class RuleClass; };
QT_END_NAMESPACE

class Rule : public QMainWindow
{
	Q_OBJECT

public:
	Rule(QWidget *parent = nullptr,Menu* menu=nullptr);
	~Rule();

public slots:
	void Exit();

private:
	Menu* mainMenu;
	Ui::RuleClass *ui;
};
