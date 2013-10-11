#ifndef OURTRACK_H
#define OURTRACK_H

#include "ui_ourtrack.h"
#include "proxyserver.h"
#include <QVector>

//-------------------------------------------------------------------

// Столбцы поисковой выдачи
#define COL_COUNT   7
#define COL_HEADER  "Category" << "Name" << "Date" << "Size" << "SE" << "LE" << "Magnet"

// Подключение, отключение работы через прокси (для отключения - закомментировать)
//#define PROXY_SERVER

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

  // Сериализация и десериализация предметов списка ( представление вектора items в виде char )
  QByteArray  Serialize();
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
