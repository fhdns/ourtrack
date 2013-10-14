#include "ourtrack.h"
#include <QFile>
#include <QList>

//-------------------------------------------------------------------

ourtrack::ourtrack(QWidget *parent)
  : QMainWindow(parent)
{
  ui.setupUi(this);    
  QObject::connect(ui.ButtonFind, SIGNAL(clicked()), this, SLOT(SendFindQuery()));

  // Загружаем конфигурацию
  ConfLoad();

  // Сокет для соединения с сервером
  socket = new QTcpSocket(this);
  connect(socket, SIGNAL(readyRead()), this, SLOT(slotReadServer()));
  // Привязка прокси-сервера к сокету
#ifdef PROXY_SERVER
  proxy_srv = new ProxyServer(socket);
  proxy_srv->start();
#endif
}

//-------------------------------------------------------------------

ourtrack::~ourtrack()
{
  socket->close();
  delete socket;
#ifdef PROXY_SERVER
  proxy_srv->stop();
  delete proxy_srv;
#endif
}

//-------------------------------------------------------------------

bool ourtrack::ConfLoad()
{
  // Открываем файл с со списком достпных адресов серверов
  QFile hosts(SERVER_HOSTS_PATH);
  if(!hosts.open(QIODevice::ReadWrite))
  {
    return 0;
  }

  while (!hosts.atEnd())
  {
    char sep = 0x3A; // ":"
    QList<QByteArray> current_host_info = hosts.readLine().split(sep);  

    host_info addr;
    addr.host = current_host_info.at(0);
    addr.port = current_host_info.at(1).toULongLong();
    avaible_hosts.push_back(addr);
  }

  hosts.close();
  return 1;
}

//-------------------------------------------------------------------
void ourtrack::ShowList()
{
  QTableWidget *table = ui.TableResult;

  if (!table) return;

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
  // Забираем запрос с формы
  QString search_query = ui.EditFind->text();

  // Если запрос меньше требуемого размера, говорим ему об этом
  if (search_query.length() < MIN_CHAR_SEARCH)
  {    
    msgBox.setText("Минимальная длина поискового запроса - " + QString::number(MIN_CHAR_SEARCH) + " символа(ов)");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
    return;
  }

  QByteArray sbuf(search_query.toStdString().c_str());

  // Соединяемся с сервером
  host_info server_addr = GetRandomHost();
  socket->connectToHost(server_addr.host, server_addr.port);
  if (!socket->waitForConnected(TIME_WAIT_FOR_CONNECT))
  {
    socket->close();
    return;
  }  

  // Отправляем наш поисковый запрос
  socket->write(sbuf);
  if (!socket->waitForBytesWritten(TIME_WAIT_FOR_WRITTEN))
  {
    socket->close();
    return;
  }
}

//-------------------------------------------------------------------

void ourtrack::slotReadServer()
{
  // Получаем сокет того, кто вызвал метод
  QTcpSocket* socket = (QTcpSocket*)sender();

  // Получаем данные от сервера и десериализуем в вектор элементов списка
  QByteArray recvbuff;
  recvbuff = socket->readAll();
  DeSerialize(recvbuff);
  
  socket->close();
  ShowList();
}

//-------------------------------------------------------------------

ourtrack::host_info ourtrack::GetRandomHost()
{
  quint16 rnd = qrand();
  if (rnd > avaible_hosts.size())
    rnd %= avaible_hosts.size();

  return avaible_hosts[rnd];
}
//-------------------------------------------------------------------