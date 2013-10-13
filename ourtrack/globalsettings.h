#ifndef SETTINGS
#define SETTINGS

//-------------------------------------------------------------------
// Настройки поисковой выдачи

// Столбцы поисковой выдачи
#define COL_COUNT   7
#define COL_HEADER  "Category" << "Name" << "Date" << "Size" << "SE" << "LE" << "Magnet"

//-------------------------------------------------------------------
// Настройки соединения с сервером

//"torwikignoueupfm.onion" "25jdsgtkkvt4kkk5.onion" "localhost"
#define SERVER_HOST           "localhost"
#define SERVER_PORT           7777
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