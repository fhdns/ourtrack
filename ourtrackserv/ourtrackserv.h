#ifndef OURTRACKSERV_H
#define OURTRACKSERV_H

//-------------------------------------------------------------------

#include <QtNetwork>
#include "databasecontrol.h"

//-------------------------------------------------------------------

class ourtrackserv : public QObject
{
  Q_OBJECT

public:
  ourtrackserv(QObject *parent = 0);
  ~ourtrackserv();

  // Server control
  void on_starting();
  void on_stoping();

private slots:
  void slotNewUser();     // from signal newConnection()
  void slotReadClient();  // from signal Read()

  // Processing the client request
  void FindQueryDissect(QTcpSocket *clientSocket);  // find (FLAG_FIND)
  void AddQueryDissect(QTcpSocket *clientSocket);   // new torrent (FLAG_ADD)
  void LikeQueryDissect(QTcpSocket *clientSocket);  // add like (FLAG_LIKE)
  void GetLastQueryDissect(QTcpSocket *clientSocket);  // list last torrent (FLAG_LAST)
  void PlusDownloadQueryDissect(QTcpSocket *clientSocket);  // new download

private:
  inline bool           SocketCheck();
  inline bool           SearchQueryCheck(const QString &query);
  QByteArray            Serialize(const QVector<MainListItem> &items);
  QVector<MainListItem> DeSerialize(const QByteArray &buffer);

  DatabaseControl         db_ctrl;
  QTcpServer              *tcpServer;
  QMap<int, QTcpSocket*>  SClients;     // CLients

};

//-------------------------------------------------------------------

#endif // OURTRACKSERV_H
