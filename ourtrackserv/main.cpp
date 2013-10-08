
#include <QtCore/QCoreApplication>
#include "ourtrackserv.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ourtrackserv Service;
    QTextStream in(stdin);
    QTextStream out(stdout);
    
    QString command = argv[1];
    do
    {
      command = command.toUpper();

      if (command == "START")
        Service.on_starting();
      else if (command == "STOP")
        Service.on_stoping();
      else if (command == "STATUS")
        Service.on_status();
      
      command = in.readLine();
    }
    while (!command.isNull());

    return a.exec();
}
