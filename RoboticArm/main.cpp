#include "RoboticArm.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	RoboticArm w;
	w.show();
	return a.exec();
}
