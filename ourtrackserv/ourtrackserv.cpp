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
  QTextStream os(clientSocket);

  QString search_query = clientSocket->readAll();

  // Если длина запроса меньше требуемой, то предварительно закрываем сокет
  if (!SearchQueryCheck(search_query))
  {    
    clientSocket->close();
    SClients.remove(idusersocs);
    return;
  }

  qDebug() << search_query;

  QVector<MainListItem> search_results;                 // результат выборки, которы будет отпарвлен клиенту
  db_ctrl.GetFindResult(search_query, search_results);  // функция выборки, заполяет search_results

  QByteArray sbuff = Serialize(search_results);         // сериализуем в пригодный для отправки буффер

  QFile a("temp");
  a.open(QIODevice::WriteOnly);
  QDataStream o(&a);
  o << sbuff;
  a.close();

  clientSocket->write(sbuff);                           // пишем в сокет

  if (!clientSocket->waitForBytesWritten())
  {
    qDebug() << "Send Time limit. size: " << QString::number(sbuff.size())
             << " client: " << QString::number(idusersocs);
  }

  clientSocket->close();
  SClients.remove(idusersocs);
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