#include "BattleField.h"
#include <QtWidgets/QApplication>
#include "Menu.h"
#include <vector>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	Menu menu;
	menu.show();
	return a.exec();
}
