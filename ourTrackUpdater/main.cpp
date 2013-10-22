#include "ourtrackupdater.h"
#include <qcoreapplication.h>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ourTrackUpdater w;

	w.argList = QCoreApplication::arguments();

	w.processUpdate();
	w.show();
	return a.exec();
}
