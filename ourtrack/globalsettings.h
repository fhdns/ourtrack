#ifndef SETTINGS
#define SETTINGS

//-------------------------------------------------------------------
// Настройки поисковой выдачи

// Столбцы поисковой выдачи
#define COL_COUNT             9
#define NUM_COL_DESCRIPTION   3
#define COL_HEADER            "ID" << \
                              "Category" << \
                              "Name" << \
                              "Desription" << \
                              "Size" << \
                              "Register" << \
                              "Hash" << \
                              "User" << \
                              "Liked"

// Минимум букв для поисковой строки
#define MIN_CHAR_SEARCH       4 

// Максимальный размер буффера, который читаем за один раз из сокета
#define MAX_SIZE_RECV         128

// Адрес страницы приземления
#define PROMO_PAGE_URL        "http://ourtrack.ru"
// Файлы конфигурации
#define SERVER_HOSTS_PATH     "hosts.ini"


//-------------------------------------------------------------------
// Настройки ожидания соединения с сервером

#define TIME_WAIT_FOR_CONNECT 500000
#define TIME_WAIT_FOR_WRITTEN 200000

//-------------------------------------------------------------------
// Настройки работы в анонимной сети (через прокси-сервер)

// Подключение, отключение работы через прокси (для отключения - закомментировать следующую строку)
//#define PROXY_SERVER
#define PROXY_HOST            "127.0.0.1"
#define PROXY_PORT            9050
#define PROXY_SRV_PATH        "proxy_srv//tor//tor.exe"

//-------------------------------------------------------------------

#endif