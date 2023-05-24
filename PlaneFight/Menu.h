#ifndef MENU_H
#define MENU_H

#include "ui_Menu.h"
#include "BattleField.h"
#include <QWidget>
#include <qstackedwidget.h>
#include <qpushbutton.h>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace Ui {
class MenuClass;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();
    QStackedWidget* stackWidget;
    QPushButton* gameModes[3];
    QWidget* gameWidgets[4];
    QVBoxLayout menuButtonLayout;
    QHBoxLayout mainLayout;

public slots:
    void GameMode1();
    void GameMode2();
    void GameMode3();

private:
    Ui::MenuClass *ui;
};

#endif // MENU_H
