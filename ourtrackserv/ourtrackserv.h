#ifndef OURTRACKSERV_H
#define OURTRACKSERV_H

#include <QtNetwork>
#include <QObject>
#include <QByteArray>
#include <QDebug>

class QTcpServer;

class ourtrackserv : public QObject
{
  Q_OBJECT

public:
    ourtrackserv(QObject *parent = 0);
    ~ourtrackserv();
    
public slots:
    void on_starting();
    void on_stoping();
    void newuser();
    void slotReadClient();
    void on_online();
    
private:
    quint64 port;
    QTcpServer *tcpServer;
    int server_status;
    QMap<int,QTcpSocket *> SClients;    
};

#endif // OURTRACKSERV_H
