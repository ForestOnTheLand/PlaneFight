#pragma once

#include <QWidget>
#include "ui_Rule.h"

QT_BEGIN_NAMESPACE
namespace Ui { class RuleClass; };
QT_END_NAMESPACE

class Rule : public QWidget
{
	Q_OBJECT

public:
	Rule(QWidget *parent = nullptr);
	~Rule();

private:
	Ui::RuleClass *ui;
};
