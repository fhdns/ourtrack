#ifndef CONNECTION_H
#define CONNECTION_H

#include "globalsettings.h"
#include "proxyserver.h"
#include <QObject>
#include <QMutex>

class Connection : public QObject
{
  Q_OBJECT

public:
  Connection(QObject *parent = 0);
  ~Connection();
  bool Send(const QByteArray *sbuff, char flag = FLAG_FIND);

private slots:
  void Read();

Q_SIGNALS:
  void SignalReadFinish(QByteArray*);

private:
  bool ConnectToServer();
  void DisconnectFromServer();

  // Buffer for server response
  QByteArray data;

  // Work with network
  QTcpSocket            *socket;
  ProxyServer           *proxy_srv;   // for anonymous proxy server
  
  // Connecting to server
  // avaiable addr servers (from SERVER_HOSTS_PATH)
  struct host_info
  {
    QString host;
    quint64 port;
  };
  QVector<host_info> avaiable_hosts;
  host_info          GetRandomHost();          // from hosts.ini  
  bool               ConfLoad();               // load hosts.ini
};

#endif // CONNECTION_H
