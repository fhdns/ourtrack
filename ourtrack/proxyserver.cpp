#include "proxyserver.h"

//-------------------------------------------------------------------

ProxyServer::ProxyServer(QTcpSocket *sock, QObject *parent)
  : QObject(parent)
{
  socket = sock;
}

//-------------------------------------------------------------------

ProxyServer::~ProxyServer()
{
}

//-------------------------------------------------------------------

bool ProxyServer::start()
{  
  ProcServ.start(PROXY_SRV_PATH);

  if (!ProcServ.waitForStarted())
  {
    ProcServ.terminate();
    return false;
  }

  QNetworkProxy prox(QNetworkProxy::Socks5Proxy, PROXY_HOST, PROXY_PORT);
  socket->setProxy(prox);  
  return true;
}

//-------------------------------------------------------------------

bool ProxyServer::stop()
{   
  ProcServ.terminate();
  return (ProcServ.waitForFinished()) ? true : false;
}

//-------------------------------------------------------------------