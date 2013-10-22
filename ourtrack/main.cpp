#include "ourtrack.h"
#include <QtWidgets/QApplication>

#include "fvupdater.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	//QApplication::setApplicationName("ourtrack");
	//QApplication::setApplicationVersion("1.0.0");
	QApplication::setOrganizationName("ourtrack");
    QApplication::setOrganizationDomain("ourtrack.ru");


	FvUpdater::sharedUpdater()->SetFeedURL("http://ourtrack.ru/appcast.xml");


	// проверить наличие обновлений
	FvUpdater::sharedUpdater()->CheckForUpdatesSilent();
	
    ourtrack w;
    w.show();
    return a.exec();
}