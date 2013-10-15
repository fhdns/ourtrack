#include "ourtrack.h"
#include <QFile>
#include <QList>

//-------------------------------------------------------------------

ourtrack::ourtrack(QWidget *parent)
  : QMainWindow(parent)
{
  ui.setupUi(this);    
  QObject::connect(ui.ButtonFind, SIGNAL(clicked()), this, SLOT(SendFindQuery()));
  QObject::connect(ui.TableResult, SIGNAL(itemPressed(QTableWidgetItem *)), this, SLOT(ResultItemActivated(QTableWidgetItem *)));

  ui.DescriptionBrowser->setUrl(QUrl(PROMO_PAGE_URL));

  // Загружаем конфигурацию
  ConfLoad();

  // Сокет для соединения с сервером
  socket = new QTcpSocket(this);
  connect(socket, SIGNAL(readyRead()), this, SLOT(ReadServer()));
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

  // Если хосты не определены, то пускаем юзера в программу, но отключаем возможность соединения
  if (!avaible_hosts.size())
  {    
    msgBox.setText(QString("Не найдено ни одной записи %1").arg(SERVER_HOSTS_PATH));
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.exec();
    ui.ButtonFind->setEnabled(0);
  }
  return 1;
}

//-------------------------------------------------------------------
void ourtrack::ShowList()
{
  QTableWidget *table = ui.TableResult;

  if (!table) return;
  
  if (!items.size())
  {    
    msgBox.setText("Ничего не найдено");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
    return;
  }

  table->setSortingEnabled(false);
  table->clear();
  table->setColumnCount(COL_COUNT);
  table->setRowCount(items.size());

  QStringList header_lst;
  header_lst << COL_HEADER;
  table->setHorizontalHeaderLabels(header_lst);

  for ( auto i = 0; i < items.size(); i++ )
  {
    for ( auto j = 0; j < COL_COUNT; j++ )
    {
      auto *ListItem = new QTableWidgetItem(items[i].Data[j]);
      table->setItem(i, j, ListItem);

      int len = items[i].Data[j].size();
      if (!i)  table->setColumnWidth(j, len*10);
    }    
  }
    
  table->setSortingEnabled(true);
}

//-------------------------------------------------------------------

void ourtrack::ResultItemActivated(QTableWidgetItem *item)
{
  int elem_num = item->row();
  ui.DescriptionBrowser->setHtml(items[elem_num].Data[NUM_COL_DESCRIPTION]);
  return;
}

//-------------------------------------------------------------------

void ourtrack::SendFindQuery()
{
  // Забираем запрос с формы
  QString search_query = ui.EditFind->text();
  // Убираем лишние пробелы
  search_query.replace("  ", " ");

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
    msgBox.setText(QString("Превышено время ожидания соединения"));
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.exec();
    socket->close();
    return;
  }  

  // Отправляем наш поисковый запрос
  socket->write(sbuf);
  if (!socket->waitForBytesWritten(TIME_WAIT_FOR_WRITTEN))
  {    
    msgBox.setText(QString("Превышено время ожидания отправки поискового запроса"));
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.exec();
    socket->close();
    return;
  }
}

//-------------------------------------------------------------------

void ourtrack::ReadServer()
{
  // Получаем сокет того, кто вызвал метод
  QTcpSocket* socket = (QTcpSocket*)sender();

  // Получаем данные от сервера и десериализуем в вектор элементов списка
  QByteArray recvbuff;

  while (!socket->atEnd())
  {
    recvbuff.push_back(socket->read(MAX_SIZE_RECV));
    socket->waitForReadyRead();
  }

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