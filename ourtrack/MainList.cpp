#include "MainList.h"

MainList::MainList(QTableWidget* TableResult, QLineEdit* find)
{
  table = TableResult;
  find_line = find;
}

void MainList::ShowList()
{
  if (!table) return;
  if (!items.size()) return;

  table->clear();
  table->setColumnCount(COL_COUNT);
  table->setRowCount(items.size());

  QStringList header_lst;
  header_lst << COL_HEADER;
  table->setHorizontalHeaderLabels(header_lst);

  for ( auto i = 0; i < items.size(); i++ )
    for ( auto j = 0; j < COL_COUNT; j++ )
    {
      auto *ListItem = new QTableWidgetItem(items[i].Data[j]);
      table->setItem(i, j, ListItem);
    }
}

void MainList::GetFindResult()
{
  ShowList();
}