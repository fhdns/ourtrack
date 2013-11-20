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

  // Управление сервером
  void on_starting();
  void on_stoping();

private slots:
  void slotNewUser();     // Вызывается при новом соединении
  void slotReadClient();  // Вызывается при чтении сокета клиента

  // Обработка запроса клиента в зависимости от флага
  void FindQueryDissect(QTcpSocket *clientSocket);  // Разбор запросов поиска (FLAG_FIND)
  void AddQueryDissect(QTcpSocket *clientSocket);   // Разбор запроса добавления нового торрента (FLAG_ADD)
  void LikeQueryDissect(QTcpSocket *clientSocket);  // Разбор добавления лайка (FLAG_LIKE)
  void GetLastQueryDissect(QTcpSocket *clientSocket);  // Список последних раздач (FLAG_LAST)
  void PlusDownloadQueryDissect(QTcpSocket *clientSocket);  // Разбор добавления числа скачек

private:
  inline bool           SocketCheck();
  inline bool           SearchQueryCheck(const QString &query);
  QByteArray            Serialize(const QVector<MainListItem> &items);
  QVector<MainListItem> DeSerialize(const QByteArray &buffer);

  DatabaseControl         db_ctrl;      // Модуль работы с БД
  QTcpServer              *tcpServer;   // Сервер приема соединений
  QMap<int, QTcpSocket*>  SClients;     // Соединенные клиенты

};

//-------------------------------------------------------------------

#endif // OURTRACKSERV_H
