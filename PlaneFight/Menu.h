#ifndef MENU_H
#define MENU_H

#include "ui_Menu.h"
#include "BattleField.h"
#include <QWidget>
#include <qstackedwidget.h>
#include <qpushbutton.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <vector>

namespace Ui {
	class MenuClass;
}

class Menu : public QWidget {
	Q_OBJECT

public:
	explicit Menu(QWidget* parent = nullptr);
	~Menu();
	QStackedWidget* stackWidget;
	std::vector<QPushButton*> startButtons;
	std::vector<QPushButton*> gameModes;
	std::vector<QWidget*> gameWidgets;
	QVBoxLayout menuButtonLayout;
	QHBoxLayout mainLayout;
	std::vector<QWidget*> to_remove;

public slots:
	void GameMode1();
	void GameMode2();
	void GameMode3();
	void StartGame();
	void Leave();
	void ShowRules();
private:
	Ui::MenuClass* ui;
};

#endif    // MENU_H
