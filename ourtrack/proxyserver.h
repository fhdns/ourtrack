#ifndef PROXYSERVER_H
#define PROXYSERVER_H

#include <QObject>
#include <QtNetwork>
#include <QProcess>

//-------------------------------------------------------------------

#define PROXY_HOST            "127.0.0.1"
#define PROXY_PORT            9050
#define PROXY_SRV_PATH        "proxy_srv//tor//tor.exe"

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
