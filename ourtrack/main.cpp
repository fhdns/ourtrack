#include "ourtrack.h"
#include <QApplication>

//-------------------------------------------------------------------

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ourtrack w;
    w.show();
    return a.exec();
}

//-------------------------------------------------------------------
