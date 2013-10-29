#ifndef MAINLISTITEM
#define MAINLISTITEM

//-------------------------------------------------------------------

// Столбцы поисковой выдачи
#define COL_COUNT             9

//-------------------------------------------------------------------

// Элемент поисковой выдачи
struct MainListItem
{
  int       id;
  int       category;
  QString   name;
  QString   description;
  int       size;
  QString   reg_time;
  QString   hash;
  int       user_id;
  int       liked;
};

//-------------------------------------------------------------------
#endif //MAINLISTITEM