#ifndef OURTRACK_H
#define OURTRACK_H

#include "ui_ourtrack.h"
#include "proxyserver.h"
#include "mainlistitem.h"
#include <QVector>
#include <QMessageBox>

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

private:  
  
  // Вывод вектора поисковой выдачи в tableView
  void ShowList();

  // Сериализация и десериализация предметов списка ( представление вектора items в виде QByteArray )
  //QByteArray  Serialize();
  void        DeSerialize(QByteArray &buffer);

  // Пользовательский интерфейс
  Ui::ourtrackClass     ui;
  QMessageBox           msgBox;

  // Список элементов поисковой выдачи
  QVector<MainListItem> items;

  // Работа с сетью
  QTcpSocket            *socket;
  ProxyServer           *proxy_srv;
};

//-------------------------------------------------------------------

#endif // OURTRACK_H
