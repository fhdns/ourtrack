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
    return 0;
  }
  QNetworkProxy prox(QNetworkProxy::Socks5Proxy, PROXY_HOST, PROXY_PORT);
  socket->setProxy(prox);  
  return 1;
}

//-------------------------------------------------------------------

bool ProxyServer::stop()
{   
  ProcServ.terminate();
  return 1;
}

//-------------------------------------------------------------------