#include "ourtrackserv.h"

ourtrackserv::ourtrackserv(QObject *parent)
  : QObject(parent)
{
  server_status = 0;
  port = 7777;
}

ourtrackserv::~ourtrackserv()
{
}

void ourtrackserv::on_starting()
{
  if (server_status)
  {
    qDebug() << "Server already running";
    return;
  }

  tcpServer = new QTcpServer(this);
  connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newuser()));
  if (!tcpServer->listen(QHostAddress::Any, port) && !server_status)
  {
    qDebug() <<  QObject::tr("Unable to start the server: %1.").arg(tcpServer->errorString());
  }
  else
  {
    server_status = 1;
    qDebug() << tcpServer->isListening() << "TCPSocket listen on port";
    qDebug() << QString::fromUtf8("Server started!");
  }
}

void ourtrackserv::on_stoping()
{
  if(server_status)
  {
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
    server_status = 0;
  }
}

void ourtrackserv::newuser()
{
  if(server_status)
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

void ourtrackserv::on_online()
{
    qDebug() << QString::fromUtf8("Online users: %1").arg(SClients.size());
}