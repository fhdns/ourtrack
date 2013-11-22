#ifndef SETTINGS
#define SETTINGS

//-------------------------------------------------------------------

#define COL_HEADER            tr("ID") << \
                              tr("Category") << \
                              tr("Name") << \
                              tr("Size") << \
                              tr("Register") <<\
                              tr("Downloads") <<\
                              tr("Likes")

#define DEFAULT_CATEGORIES    tr("Unkown") << \
                              tr("Video") << \
                              tr("Audio") << \
                              tr("Games") << \
                              tr("Soft") << \
                              tr("Books") << \
                              tr("Other")

#define TEMPLATE_PATH         "template//"

// Minimum symbols for search line
#define MIN_CHAR_SEARCH       4 
// Minimum symbols for new torrent name
#define MIN_CHAR_ADD_NAME     10 
// Minimum symbols for description new torrent
#define MIN_CHAR_ADD_DESC     100 

// Max recv buffer size per one time
#define MAX_SIZE_RECV         128

// Start page
#define PROMO_PAGE_URL        "http://ourtrack.ru"
// Configuration files
#define SERVER_HOSTS_PATH     "hosts.ini"


//-------------------------------------------------------------------
// Settings waiting servers

#define TIME_WAIT_FOR_CONNECT 500000
#define TIME_WAIT_FOR_WRITTEN 200000

//-------------------------------------------------------------------
// Settings work in anonymous network (proxy)

// Activate work proxy-server. Define PROXY_SERVER - enabled
//#define PROXY_SERVER
#define PROXY_HOST            "127.0.0.1"
#define PROXY_PORT            9050
#define PROXY_SRV_PATH        "proxy_srv//tor//tor.exe"

// Server flags
#define FLAG_FIND       0x00
#define FLAG_ADD        0x01
#define FLAG_LIKED      0x02
#define FLAG_LAST       0x03
#define FLAG_PLDOWN     0x04

//-------------------------------------------------------------------

#endif