#ifndef MAINLISTITEM
#define MAINLISTITEM

//-------------------------------------------------------------------

// Столбцы поисковой выдачи
#define COL_COUNT             10

//-------------------------------------------------------------------

// Элемент поисковой выдачи
struct MainListItem
{
  int       id;
  int       category;
  QString   name;
  QString   description;
  long long size;
  QString   reg_time;
  QString   hash;
  int       user_id;
  int       download;
  int       liked;
};

//-------------------------------------------------------------------

#endif // MAINLISTITEM