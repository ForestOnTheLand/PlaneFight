#include "Menu.h"

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	Menu menu;
	menu.setMouseTracking(true);
	menu.show();
	return a.exec();
}
