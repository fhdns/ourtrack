#ifndef PROXYSERVER_H
#define PROXYSERVER_H

//-------------------------------------------------------------------

#include <QtNetwork>
#include <QProcess>
#include "globalsettings.h"

//-------------------------------------------------------------------

class ProxyServer : public QObject
{
  Q_OBJECT

public:
  ProxyServer(QTcpSocket *sock, QObject *parent = 0);
  ~ProxyServer();

  // Proxy-srv control
  bool  start();
  bool  stop();

private:
  QTcpSocket  *socket;
  QProcess    ProcServ;
};

//-------------------------------------------------------------------

#endif // PROXYSERVER_H
