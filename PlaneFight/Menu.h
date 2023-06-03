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
#include <qcommandlinkbutton.h>

namespace Ui {
	class MenuClass;
}

class Menu : public QWidget {
	Q_OBJECT

public:
	explicit Menu(QWidget* parent = nullptr);
	~Menu();

public:
	int mode;  //to choose the review interface
	std::vector<QPushButton*> startButtons;
	std::vector<QLabel*> startLabels;
	std::vector<QPushButton*> gameModes;
	std::vector<QLabel*> modeLabels;
	std::vector<QWidget*> gameWidgets;
	std::vector<QWidget*> to_remove;
	QLabel* Title;
	QPushButton* toFirstPage;
	QStackedWidget* stackWidget;
	QVBoxLayout menuButtonLayout;
	QHBoxLayout mainLayout;

public slots:
	void GameMode1();
	void GameMode2();
	void GameMode3();
	void StartGame();
	void Leave();
	void ShowRules();
	void mouseMoveEvent(QMouseEvent* _event);
	void ToFirstPage();

private:
	Ui::MenuClass* ui;
};

#endif    // MENU_H
