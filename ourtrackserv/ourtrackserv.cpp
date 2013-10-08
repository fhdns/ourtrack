#include "ourtrackserv.h"

ourtrackserv::ourtrackserv(QObject *parent)
  : QObject(parent)
{
  tcpServer = new QTcpServer(this);
  port = 7777;
}

ourtrackserv::~ourtrackserv()
{
  on_stoping();
  delete tcpServer;
}

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

  tcpServer->newConnection();

  if (tcpServer->listen(QHostAddress::Any, port))
  {
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newuser()));
    qDebug() << QString::fromUtf8("Server started!");
    qDebug() << "TCPSocket listen on port " << tcpServer->serverPort();
  }
  else
  {
    qDebug() <<  QObject::tr("Unable to start the server: %1.").arg(tcpServer->errorString());
  }
}

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

void ourtrackserv::newuser()
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

void ourtrackserv::slotReadClient()
{
  QTcpSocket* clientSocket = (QTcpSocket*)sender();
  int idusersocs = clientSocket->socketDescriptor();
  QTextStream os(clientSocket);
  os.setAutoDetectUnicode(true);

  os << "HTTP/1.0 200 Ok\r\n"
    "Content-Type: text/html; charset=\"utf-8\"\r\n"
    "\r\n"
    "<h1>Nothing to see here</h1>\n"
    << QDateTime::currentDateTime().toString() << "\n";

  //ui->textinfo->append("ReadClient:"+clientSocket->readAll()+"\n\r");

  clientSocket->close();
  SClients.remove(idusersocs);
}

void ourtrackserv::on_status()
{  
  if(!SocketCheck()) return;
  qDebug() << "Online users: "    << SClients.size();
  qDebug() << "Is listening: "    << tcpServer->isListening();
  qDebug() << "Server Address: "  << tcpServer->serverAddress();
  qDebug() << "Server Port: "     << tcpServer->serverPort();
}

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