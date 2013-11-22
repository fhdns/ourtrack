#include "connection.h"
#include <QMessageBox>
#include <QApplication>

Connection::Connection(QObject *parent)
  : QObject(parent)
{
  socket = new QTcpSocket(this);
  connect(socket, SIGNAL(readyRead()), this, SLOT(Read()));

  // Load hosts.ini
  ConfLoad();

  // Activation Proxy-server
#ifdef PROXY_SERVER
  proxy_srv = new ProxyServer(socket);
  proxy_srv->start();
#endif
}

Connection::~Connection()
{
  DisconnectFromServer();
  delete socket;
#ifdef PROXY_SERVER
  proxy_srv->stop();
  delete proxy_srv;
#endif
}

bool Connection::ConnectToServer()
{  
  // Connecting to server
  connect_to_host:
  host_info server_addr = GetRandomHost();
  socket->connectToHost(server_addr.host, server_addr.port);
  if (!socket->waitForConnected(TIME_WAIT_FOR_CONNECT))
  {
    QMessageBox::warning(0, tr("Attention!"), tr("Connection timed out"));

    // Try again?
    if ( QMessageBox::question(0, tr("Reconnect?"), tr("Try again with another server?"),
                               QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes)
    {
      goto connect_to_host;
    }

    DisconnectFromServer();
    return false;
  } 
  return true;
}

void Connection::DisconnectFromServer()
{
  socket->close();
}

bool Connection::Send(const QByteArray *sbuff, char flag)
{  
  if (!ConnectToServer())
  {
    return false;
  }

  if (socket->state() != QAbstractSocket::ConnectedState)
  {
    QMessageBox::warning(0, tr("Attention!"), tr("Socket is not connected"));
    DisconnectFromServer();
    return false;
  }

  // Send flag
  socket->putChar(flag);

  // Send query
  socket->write(*sbuff);
  if (!socket->waitForBytesWritten(TIME_WAIT_FOR_WRITTEN))
  {        
    QMessageBox::warning(0, tr("Attention!"), tr("Timeout sending data to server"));
    DisconnectFromServer();
    return false;
  }
  return true;
}

void Connection::Read()
{
  // Get socket
  QTcpSocket* socket = (QTcpSocket*)sender();
  
  data.clear();
  while (!socket->atEnd())
  {
    data.push_back(socket->read(MAX_SIZE_RECV));
    socket->waitForReadyRead();
  }

  emit SignalReadFinish(&data);
  DisconnectFromServer(); 
}

Connection::host_info Connection::GetRandomHost()
{  
  quint16 rnd = qrand();
  if (rnd > avaiable_hosts.size())
    rnd %= avaiable_hosts.size();

  return avaiable_hosts[rnd];
}

bool Connection::ConfLoad()
{
  QFile hosts(SERVER_HOSTS_PATH);
  if(hosts.open(QIODevice::ReadWrite))
  {
    while (!hosts.atEnd())
    {
      char sep = 0x3A; // ":"
      QList<QByteArray> current_host_info = hosts.readLine().split(sep);  

      // Min 2 params: addr and port
      if (current_host_info.size() != 2) break;

      host_info addr;
      addr.host = current_host_info.at(0);
      addr.port = current_host_info.at(1).toULongLong();
      avaiable_hosts.push_back(addr);
    }
    hosts.close();
  }

  if (!avaiable_hosts.size())
  {    
    QMessageBox::critical(0, tr("Attention!"), QString(tr("No found records %1")).arg(SERVER_HOSTS_PATH));
    return false;
  }

  return true;
}