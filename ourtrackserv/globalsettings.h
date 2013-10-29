#ifndef SERV_SETTINGS
#define SERV_SETTINGS

//-------------------------------------------------------------------

// Минимум букв в поисковом запросе
#define MIN_CHAR_SEARCH 4 

// Порт прослушивания
#define LISTEN_PORT     7777

// Лимит количества результатов запрос
#define QUERY_LIMIT     1000

// Настройка базы данных
#define DB_DRIVER       "QMYSQL"
#define DB_NAME         "ourtrack"
#define DB_HOST         "localhost"
#define DB_PORT         3306
#define DB_USER         "root"
#define DB_PASS         ""

//-------------------------------------------------------------------

#endif //SERV_SETTINGS