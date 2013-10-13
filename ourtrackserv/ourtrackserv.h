#ifndef OURTRACKSERV_H
#define OURTRACKSERV_H

#include "databasecontrol.h"
#include <QtNetwork>
#include <QDebug>

//-------------------------------------------------------------------

class ourtrackserv : public QObject
{
  Q_OBJECT

public:
  ourtrackserv(QObject *parent = 0);
  ~ourtrackserv();

  void on_starting();
  void on_stoping();
  //void on_status();

private slots:
  void slotNewUser();
  void slotReadClient();


private:
  inline bool SocketCheck();
  QByteArray Serialize(QVector<MainListItem> &items);

  DatabaseControl db_ctrl;  
  quint64 port;
  QTcpServer *tcpServer;
  QMap<int,QTcpSocket *> SClients;
};

//-------------------------------------------------------------------

#endif // OURTRACKSERV_H
