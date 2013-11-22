#ifndef SERV_SETTINGS
#define SERV_SETTINGS

//-------------------------------------------------------------------

// Minimum symbols for search line
#define MIN_CHAR_SEARCH       4 
// Minimum symbols for new torrent name
#define MIN_CHAR_ADD_NAME     10 
// Minimum symbols for description new torrent
#define MIN_CHAR_ADD_DESC     100 
 
#define LISTEN_PORT     7777

// Db select limit
#define QUERY_LIMIT     100
// for get last
#define QUERY_LASTLIMIT 100

// Db settings
#define DB_DRIVER       "QMYSQL"
#define DB_NAME         "ourtrack"
#define DB_HOST         "localhost"
#define DB_PORT         3306
#define DB_USER         "root"
#define DB_PASS         ""

// Flags
#define FLAG_FIND       0x00
#define FLAG_ADD        0x01
#define FLAG_LIKED      0x02
#define FLAG_LAST       0x03
#define FLAG_PLDOWN     0x04


//-------------------------------------------------------------------

#endif //SERV_SETTINGS