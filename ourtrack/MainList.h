#pragma once
#include "ui_ourtrack.h"
#include <vector>
#include <QStandardItemModel>
using namespace std;

#define COL_COUNT   7
#define COL_HEADER  "Category" << "Name" << "Date" << "Size" << "SE" << "LE" << "Magnet"

struct MainListItem
{
  //QString category;
  //QString name;
  //QString date;
  //QString size;
  //QString se;
  //QString le;
  //QString magnet;
  QString Data[COL_COUNT];
};

class MainList
{
public:
  MainList(QTableWidget* TableResult = 0, QLineEdit* find = 0);

  void GetFindResult();
  void ShowList();

private:  
  vector<MainListItem>  items;
  QTableWidget          *table;
  QLineEdit             *find_line;
};