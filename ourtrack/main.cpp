#include "ourtrack.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ourtrack w;

    //MainList *List = new MainList(w.ui.TableResult, w.ui.EditFind);
    //QObject::connect(w.ui.ButtonFind, SIGNAL(clicked()), &w, SLOT(List->ShowList()));
    //QObject::connect(w.ui.ButtonFind, SIGNAL(clicked()), &List, SLOT(ShowList()));

    w.show();
    return a.exec();
}
