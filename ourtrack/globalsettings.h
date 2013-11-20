#ifndef SETTINGS
#define SETTINGS

//-------------------------------------------------------------------
// Настройки поисковой выдачи

#define COL_HEADER            tr("ID") << \
                              tr("Category") << \
                              tr("Name") << \
                              tr("Size") << \
                              tr("Register") <<\
                              tr("Downloads") <<\
                              tr("Likes")

#define DEFAULT_CATEGORIES    tr("Unkown") << \
                              tr("Видео") << \
                              tr("Аудио") << \
                              tr("Игры") << \
                              tr("Софт") << \
                              tr("Книги") << \
                              tr("Other")

#define TEMPLATE_PATH         "template//"

// Минимум символов для поисковой строки
#define MIN_CHAR_SEARCH       4 
// Минимум символов для названия нового торрента
#define MIN_CHAR_ADD_NAME     10 
// Минимум символов для описания нового торрента
#define MIN_CHAR_ADD_DESC     100 

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

// Флаги серверу
#define FLAG_FIND       0x00
#define FLAG_ADD        0x01
#define FLAG_LIKED      0x02
#define FLAG_LAST       0x03
#define FLAG_PLDOWN     0x04

//-------------------------------------------------------------------

#endif