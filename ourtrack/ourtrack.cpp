#include "ourtrack.h"

//-------------------------------------------------------------------

//"torwikignoueupfm.onion" "25jdsgtkkvt4kkk5.onion" "localhost"
#define SERVER_HOST           "localhost"
#define SERVER_PORT           7777
#define TIME_WAIT_FOR_CONNECT 100000
#define TIME_WAIT_FOR_WRITTEN 100000

//-------------------------------------------------------------------

ourtrack::ourtrack(QWidget *parent)
  : QMainWindow(parent)
{
  ui.setupUi(this);    
  QObject::connect(ui.ButtonFind, SIGNAL(clicked()), this, SLOT(SendFindQuery()));

  // Сокет для соединения с сервером
  socket = new QTcpSocket(this);
  connect(socket,SIGNAL(readyRead()),this, SLOT(slotReadServer()));
  // Привязка прокси-сервера к сокету
#ifdef PROXY_SERVER
  proxy_srv = new ProxyServer(socket);
  proxy_srv->start();
#endif
}

//-------------------------------------------------------------------

ourtrack::~ourtrack()
{
  delete socket;
#ifdef PROXY_SERVER
  proxy_srv->stop();
  delete proxy_srv;
#endif
}

//-------------------------------------------------------------------

void ourtrack::ShowList()
{
  QTableWidget *table = ui.TableResult;

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

//-------------------------------------------------------------------

void ourtrack::SendFindQuery()
{
  ShowList(); return;
  // Забираем запрос с формы
  QString search_query = ui.EditFind->text();
  QByteArray sbuf(search_query.toStdString().c_str());

  // Соединяемся с сервером
  socket->connectToHost(SERVER_HOST, SERVER_PORT);
  if (!socket->waitForConnected(TIME_WAIT_FOR_CONNECT))
  {
    socket->close();
    return;
  }  

  // Отправляем наш поисковый запрос
  socket->write(sbuf);
  if (socket->waitForBytesWritten(TIME_WAIT_FOR_WRITTEN))
  {
    socket->close();
    return;
  }

  // Закрываем сокет (кэп одобрил)
  socket->close();
}

//-------------------------------------------------------------------

void ourtrack::slotReadServer()
{
  // Получаем сокет того, кто вызвал метод
  QTcpSocket* socket = (QTcpSocket*)sender();

  // Получаем данные от сервера и десериализуем в вектор элементов списка
  QByteArray recvbuff = socket->readAll();
  DeSerialize(recvbuff);

  socket->close();
  ShowList();
}

//-------------------------------------------------------------------
