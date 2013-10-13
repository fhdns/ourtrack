#ifndef OURTRACK_H
#define OURTRACK_H

#include "ui_ourtrack.h"
#include "proxyserver.h"
#include <QVector>

//-------------------------------------------------------------------

// Элемент поисковой выдачи
struct MainListItem
{
  QString Data[COL_COUNT];
};

//-------------------------------------------------------------------

class ourtrack : public QMainWindow
{
  Q_OBJECT

public:
  ourtrack(QWidget *parent = 0);
  ~ourtrack();

public slots:
  void SendFindQuery();
  void slotReadServer();
  void ShowList();

private:  

  // Сериализация и десериализация предметов списка ( представление вектора items в виде QByteArray )
  //QByteArray  Serialize();
  void        DeSerialize(QByteArray &buffer);

  // Пользовательский интерфейс
  Ui::ourtrackClass     ui;

  // Список элементов поисковой выдачи
  QVector<MainListItem> items;

  // Работа с сетью
  QTcpSocket            *socket;
  ProxyServer           *proxy_srv;
};

//-------------------------------------------------------------------

#endif // OURTRACK_H
