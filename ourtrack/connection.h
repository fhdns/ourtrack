#ifndef CONNECTION_H
#define CONNECTION_H

#include "globalsettings.h"
#include "proxyserver.h"
#include <QObject>
#include <QMutex>

// Флаги серверу
#define FLAG_FIND       0x00
#define FLAG_ADD        0x01
#define FLAG_LIKED      0x02

class Connection : public QObject
{
  Q_OBJECT

public:
  Connection(QObject *parent = 0);
  ~Connection();
  void Send(const QByteArray *sbuff, char flag = FLAG_FIND);

private slots:
  void Read();

Q_SIGNALS:
  void SignalReadFinish(QByteArray*);

private:
  bool ConnectToServer();
  void DisconnectFromServer();

  // Буффер, в который записывается ответ от сервера
  QByteArray data;

  // Работа с сетью
  QTcpSocket            *socket;
  ProxyServer           *proxy_srv;   // Модуль работы с прокс-сервером
  
  // Подключение к серверу
  // Доступные адреса расположения сервера (из файла SERVER_HOSTS_PATH)
  struct host_info
  {
    QString host;
    quint64 port;
  };
  QVector<host_info> avaible_hosts;
  host_info          GetRandomHost();          // Выбирает случайный адрес из списка hosts.ini  
  bool               ConfLoad();               // Загрузить список хостов 
};

#endif // CONNECTION_H
