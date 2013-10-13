#ifndef PROXYSERVER_H
#define PROXYSERVER_H

#include "globalsettings.h"
#include <QtNetwork>
#include <QProcess>

//-------------------------------------------------------------------

class ProxyServer : public QObject
{
  Q_OBJECT

public:
  ProxyServer(QTcpSocket *sock, QObject *parent = 0);
  ~ProxyServer();

  // Управление прокси-сервером
  bool  start();
  bool  stop();

private:
  QTcpSocket  *socket;
  QProcess    ProcServ;
};

//-------------------------------------------------------------------

#endif // PROXYSERVER_H
