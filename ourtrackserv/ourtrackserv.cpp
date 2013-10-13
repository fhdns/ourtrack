#include "ourtrackserv.h"
#include <QByteArray>

//-------------------------------------------------------------------

ourtrackserv::ourtrackserv(QObject *parent)
  : QObject(parent)
{
  db_ctrl.connect_db();
  tcpServer = new QTcpServer(this);
  port = 7777;
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

  if (tcpServer->listen(QHostAddress::Any, port))
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
    QTextStream os(SClients[i]);
    os.setAutoDetectUnicode(true);
    os << QDateTime::currentDateTime().toString() << "\n";
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
  qDebug() << search_query;

  QVector<MainListItem> search_results;
  db_ctrl.GetFindResult(search_query, search_results);

  clientSocket->write(Serialize(search_results));
  if (clientSocket->waitForBytesWritten())
  {
    clientSocket->close();
    SClients.remove(idusersocs);
    return;
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
    return false;
  }
  else if (!tcpServer->isListening())
  {
    qDebug() << "QTcpServer is not running";
    return false;
  }
  return true;
}
//-------------------------------------------------------------------
