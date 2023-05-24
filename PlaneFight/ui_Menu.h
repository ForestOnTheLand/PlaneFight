/********************************************************************************
** Form generated from reading UI file 'BattleField.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENU_H
#define UI_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MenuClass
{
public:
    QLabel* score_label;
    QLabel* hp_label;

    void setupUi(QWidget* MenuClass)
    {
        if (MenuClass->objectName().isEmpty())
            MenuClass->setObjectName("MenuClass");
        MenuClass->resize(800, 800);
        MenuClass->setMinimumSize(QSize(800, 800));
        MenuClass->setMaximumSize(QSize(800, 800));

        retranslateUi(MenuClass);

        QMetaObject::connectSlotsByName(MenuClass);
    } // setupUi

    void retranslateUi(QWidget* MenuClass)
    {
        MenuClass->setWindowTitle(QCoreApplication::translate("MenuClass", "Menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MenuClass : public Ui_MenuClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BATTLEFIELD_H
