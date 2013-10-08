#include "ourtrack.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ourtrack w;
    
    //sock->connectToHost("localhost",7777);
    //sock = new QTcpSocket(a);

    /*if (sock->waitForConnected(1000))
     qDebug("Connected!");*/

    w.show();
    return a.exec();
}