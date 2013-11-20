#include "ourtrackserv.h"
#include <QByteArray>
#include <QDebug>

//-------------------------------------------------------------------

ourtrackserv::ourtrackserv(QObject *parent)
  : QObject(parent)
{
  db_ctrl.connect_db();
  tcpServer = new QTcpServer(this);
}

//-------------------------------------------------------------------

ourtrackserv::~ourtrackserv()
{
  db_ctrl.disconnect_db();
  on_stoping();
  delete tcpServer;
}

//-------------------------------------------------------------------

void ourtrackserv::on_starting()
{
  if (tcpServer->isListening())
  {
    qDebug() << "QTcpServer already is running";
    return;
  }

  if (!tcpServer->listen(QHostAddress::Any, LISTEN_PORT))
  {
    qDebug() <<  "Unable to start the server: " << tcpServer->errorString();
    return;
  }

  connect(tcpServer, SIGNAL(newConnection()), this, SLOT(slotNewUser()));
  qDebug() << "TCPSocket listen on port " << tcpServer->serverPort();
  qDebug() << "Server started!";
}

//-------------------------------------------------------------------

void ourtrackserv::on_stoping()
{
  if(!SocketCheck()) return;

  foreach(int i, SClients.keys())
  {
    SClients[i]->close();
    SClients.remove(i);
  }

  tcpServer->close();
  qDebug() << QString::fromUtf8("Server is shutdown!");
}

//-------------------------------------------------------------------

void ourtrackserv::slotNewUser()
{
  while(tcpServer->hasPendingConnections())
  {
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
    int idusersocs = clientSocket->socketDescriptor();
    SClients[idusersocs] = clientSocket;
    connect(SClients[idusersocs], SIGNAL(readyRead()), this, SLOT(slotReadClient()));
    qDebug() << "New user connect: " << QString::number(idusersocs);
  }
}

//-------------------------------------------------------------------

void ourtrackserv::slotReadClient()
{
  QTcpSocket* clientSocket = (QTcpSocket*)sender();
  int idusersocs = clientSocket->socketDescriptor();

  // Получаем флаг запроса
  char flag;
  if (!clientSocket->getChar(&flag))
  {
    qDebug() << "Error flag read";
    clientSocket->close();
    SClients.remove(idusersocs);
    return;
  }

  switch (flag)
  {
  case FLAG_FIND:
    {
      FindQueryDissect(clientSocket);
      break;
    }
  case FLAG_ADD:
    {
      AddQueryDissect(clientSocket);
      break;
    }
  case FLAG_LIKED:
    {
      LikeQueryDissect(clientSocket);
      break;
    }
  case FLAG_LAST:
    {
      GetLastQueryDissect(clientSocket);
      break;
    }
  case FLAG_PLDOWN:
    {
      PlusDownloadQueryDissect(clientSocket);
      break;
    }
  default:
    {
      break;
    }
  }

  clientSocket->close();
  SClients.remove(idusersocs);
}

//-------------------------------------------------------------------

void ourtrackserv::FindQueryDissect(QTcpSocket *clientSocket)
{  
  int idusersocs = clientSocket->socketDescriptor();
  QString search_query = clientSocket->readAll();

  // Если длина запроса меньше требуемой, то предварительно закрываем сокет
  if (!SearchQueryCheck(search_query))
  {
    return;
  }
  qDebug() << search_query;

  QVector<MainListItem> search_results;                 // результат выборки, которы будет отпарвлен клиенту
  db_ctrl.GetFindResult(search_query, search_results);  // функция выборки, заполяет search_results

  QByteArray sbuff = Serialize(search_results);         // сериализуем в пригодный для отправки буффер

  clientSocket->write(sbuff);                           // пишем в сокет

  if (!clientSocket->waitForBytesWritten())
  {
    qDebug() << "Send Time limit. size: " << QString::number(sbuff.size())
             << " client: " << QString::number(idusersocs);
  }
}

//-------------------------------------------------------------------

void ourtrackserv::AddQueryDissect(QTcpSocket *clientSocket)
{
  QByteArray recvbuff = clientSocket->readAll();
  //Десериализуем вектор
  QVector<MainListItem> items = DeSerialize(recvbuff);

  // Проверяем значения на добавление и добавляем
  for (auto it = items.begin(); it != items.end(); it++)
  {
    // Добавляем в БД 
    db_ctrl.AddTorrentItem(*it); 
  }

}

//-------------------------------------------------------------------

void ourtrackserv::LikeQueryDissect(QTcpSocket *clientSocket)
{
  bool to_int_ok = true;
  long long id = clientSocket->readAll().toLongLong(&to_int_ok);
  if (!to_int_ok)
  {
    qDebug() << "error convert id to long";
    return;
  }
  db_ctrl.LikedTorrent(id);
}

//-------------------------------------------------------------------

void ourtrackserv::PlusDownloadQueryDissect(QTcpSocket *clientSocket)
{
  bool to_int_ok = true;
  long long id = clientSocket->readAll().toLongLong(&to_int_ok);
  if (!to_int_ok)
  {
    qDebug() << "error convert id to long";
    return;
  }
  db_ctrl.PlusDownloadTorrent(id);
}

//-------------------------------------------------------------------

void ourtrackserv::GetLastQueryDissect(QTcpSocket *clientSocket)
{
  QVector<MainListItem> search_results;                 // результат выборки, которы будет отпарвлен клиенту
  db_ctrl.GetLastResult(search_results);                // функция запроса последних добавлений, заполяет search_results

  QByteArray sbuff = Serialize(search_results);         // сериализуем в пригодный для отправки буффер
  clientSocket->write(sbuff);                           // пишем в сокет

  if (!clientSocket->waitForBytesWritten())
  {
    qDebug() << "Send Time limit. size: " << QString::number(sbuff.size());
  }
}

//-------------------------------------------------------------------

inline bool ourtrackserv::SocketCheck()
{ 
  if (!tcpServer->isListening())
  {
    qDebug() << "QTcpServer is not running";
    return false;
  }

  return true;
}
//-------------------------------------------------------------------

inline bool ourtrackserv::SearchQueryCheck(const QString &query)
{
  return (query.length() < MIN_CHAR_SEARCH) ? false : true;
}

//-------------------------------------------------------------------