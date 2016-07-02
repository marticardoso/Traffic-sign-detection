#include "signdetectorapp.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SignDetectorApp w;
	w.show();
	return a.exec();
}
