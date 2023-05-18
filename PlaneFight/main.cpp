#include "BattleField.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	BattleField w;
	w.show();
	return a.exec();
}
