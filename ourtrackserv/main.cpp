#include <QCoreApplication>
#include "ourtrackserv.h"

//-------------------------------------------------------------------

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  ourtrackserv Service;
  Service.on_starting();

  return a.exec();
}

//-------------------------------------------------------------------
