#ifndef MAINLISTITEM
#define MAINLISTITEM

//-------------------------------------------------------------------

// Columns search response
#define COL_COUNT             10

//-------------------------------------------------------------------

// Element search response
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