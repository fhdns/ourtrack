#ifndef OURTRACKSERV_H
#define OURTRACKSERV_H

#include <QtNetwork>
#include <QObject>
#include <QByteArray>
#include <QDebug>

class ourtrackserv : public QObject
{
  Q_OBJECT

public:
    ourtrackserv(QObject *parent = 0);
    ~ourtrackserv();
    
    void on_starting();
    void on_stoping();
    void on_status();

private slots:
    void newuser();
    void slotReadClient();

    inline bool SocketCheck();
    
private:
    quint64 port;
    QTcpServer *tcpServer;
    QMap<int,QTcpSocket *> SClients;    
};

#endif // OURTRACKSERV_H
