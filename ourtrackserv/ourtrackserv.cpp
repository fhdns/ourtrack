#include "ourtrackserv.h"
#include <QByteArray>

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
  if (!tcpServer)
  {    
    qDebug() << "QTcpServer does not exist";
    return;
  }
  else if (tcpServer->isListening())
  {
    qDebug() << "QTcpServer already is running";
    return;
  }

  if (tcpServer->listen(QHostAddress::Any, LISTEN_PORT))
  {
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(slotNewUser()));
    qDebug() << "TCPSocket listen on port " << tcpServer->serverPort();
    qDebug() << "Server started!";
  }
  else
  {
    qDebug() <<  QObject::tr("Unable to start the server: %1.").arg(tcpServer->errorString());
  }
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

    qDebug() << QString::fromUtf8("New user connect: %1!").arg(idusersocs);
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
  clientSocket->write(sbuff);

  if (clientSocket->waitForBytesWritten())
  {
    qDebug() << "Send Time limit. size: " << QString::number(sbuff.size())
             << " client: " << QString::number(idusersocs);
  }

  clientSocket->close();
  SClients.remove(idusersocs);
}

//-------------------------------------------------------------------

//void ourtrackserv::on_status()
//{  
//  if(!SocketCheck()) return;
//  qDebug() << "Online users: "    << SClients.size();
//  qDebug() << "Is listening: "    << tcpServer->isListening();
//  qDebug() << "Server Address: "  << tcpServer->serverAddress();
//  qDebug() << "Server Port: "     << tcpServer->serverPort();
//}

//-------------------------------------------------------------------

inline bool ourtrackserv::SocketCheck()
{  
  if (!tcpServer)
  {
    qDebug() << "QTcpServer does not exist";
    return 0;
  }
  else if (!tcpServer->isListening())
  {
    qDebug() << "QTcpServer is not running";
    return 0;
  }
  return 1;
}
//-------------------------------------------------------------------

inline bool ourtrackserv::SearchQueryCheck(QString &query)
{  
  if (query.length() < MIN_CHAR_SEARCH)
    return 0;

  return 1;
}
//-------------------------------------------------------------------