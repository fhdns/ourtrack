#include "connection.h"
#include <QMessageBox>
#include <QApplication>

Connection::Connection(QObject *parent)
  : QObject(parent)
{
  // Сокет для соединения с сервером
  socket = new QTcpSocket(this);
  connect(socket, SIGNAL(readyRead()), this, SLOT(Read()));

  // Загружаем список хостов
  ConfLoad();

  // Привязка прокси-сервера к сокету
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
  // Соединяемся с сервером
  connect_to_host:
  host_info server_addr = GetRandomHost();
  socket->connectToHost(server_addr.host, server_addr.port);
  if (!socket->waitForConnected(TIME_WAIT_FOR_CONNECT))
  {
    QMessageBox::warning(0, tr("Внимание"), tr("Превышено время ожидания соединения"));

    // Соединиться с другим сервером?
    if ( QMessageBox::question(0, tr("Переподключиться?"), tr("Попробовать еще с другим сервером?"),
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
  // Сначала проверям, есть ли соединение
  if (socket->state() != QAbstractSocket::ConnectedState)
  {
    QMessageBox::warning(0, tr("Внимание"), tr("Сокет не соединен"));
    DisconnectFromServer();
    return false;
  }

  // Отправляем флаг запроса серверу
  socket->putChar(flag);

  // Отправляем наш запрос серверу
  socket->write(*sbuff);
  if (!socket->waitForBytesWritten(TIME_WAIT_FOR_WRITTEN))
  {        
    QMessageBox::warning(0, tr("Внимание"), tr("Превышено время ожидания отправки данных серверу"));
    DisconnectFromServer();
    return false;
  }
  return true;
}

void Connection::Read()
{
  // Получаем сокет того, кто вызвал метод
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
  if (rnd > avaible_hosts.size())
    rnd %= avaible_hosts.size();

  return avaible_hosts[rnd];
}

bool Connection::ConfLoad()
{
  // Открываем файл с со списком доступных адресов серверов
  QFile hosts(SERVER_HOSTS_PATH);
  if(hosts.open(QIODevice::ReadWrite))
  {
    while (!hosts.atEnd())
    {
      char sep = 0x3A; // ":"
      QList<QByteArray> current_host_info = hosts.readLine().split(sep);  

      // Должно быть минимум 2 параметра: адрес и порт
      if (current_host_info.size() != 2) break;

      host_info addr;
      addr.host = current_host_info.at(0);
      addr.port = current_host_info.at(1).toULongLong();
      avaible_hosts.push_back(addr);
    }
    hosts.close();
  }

  // Если хосты не определены, то пускаем юзера в программу, но отключаем возможность соединения
  if (!avaible_hosts.size())
  {    
    QMessageBox::critical(0, "Внимание", QString(tr("Не найдено ни одной записи %1")).arg(SERVER_HOSTS_PATH));
    return false;
  }

  return true;
}