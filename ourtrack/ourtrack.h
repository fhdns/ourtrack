#ifndef OURTRACK_H
#define OURTRACK_H

#include "ui_ourtrack.h"
#include <vector>
#include <QtNetwork>

//#include <QAbstractSocket>

using namespace std;

#define COL_COUNT   7
#define COL_HEADER  "Category" << "Name" << "Date" << "Size" << "SE" << "LE" << "Magnet"
#define BUFF_SIZE   256

// Служебные слова
#define SERVICE_MESSAGE_FIND    "[F]"
#define SERVICE_MESSAGE_UPLOAD  "[U]"
#define SERVICE_MESSAGE_PING    "[P]"

struct MainListItem
{
  char Data[COL_COUNT][BUFF_SIZE];
};

class ourtrack : public QMainWindow
{
  Q_OBJECT

public:
  ourtrack(QWidget *parent = 0);
  ~ourtrack();

public slots:
  void GetFindResult();
  void slotReadServer();
  void ShowList();

  // Сериализация и десериализация предметов списка ( представление вектора items в виде char )
  char *ItemsSerialization(UINT &len);
  void ItemsDeSerialization(const char *buff, const UINT len);

private:  
  Ui::ourtrackClass     ui;
  vector<MainListItem>  items;
};

#endif // OURTRACK_H
