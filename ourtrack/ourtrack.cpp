#include <QFile>
#include <QList>
#include <QUrl>
#include <QStringList>
#include <QDesktopServices>
#include "ourtrack.h"

//-------------------------------------------------------------------

namespace convert
{
  QStringList default_trackers()
  {
    QStringList list;
    list << "http://retracker.local/announce";
    list << "udp://tracker.openbittorrent.com:80/announce";
    list << "udp://tracker.publicbt.com:80/announce";
    list << "udp://tracker.ccc.de:80/announce";
    return list;
  }

  QString magnetUrl(QString hash, QString name, qlonglong size, bool urlencode)
  {
    QString magnet = "magnet:?xt=urn:btih:" + hash +
      "&dn=" + (urlencode ? QUrl::toPercentEncoding(name) : name) +
      "&xl=" + QString::number(size);
    QStringList trackers_list = default_trackers();
    foreach (QString tracker, trackers_list)
    {
      if (!tracker.isEmpty())
      {
        magnet += "&tr=" + (urlencode ? QUrl::toPercentEncoding(tracker) : tracker);
      }
    }
    return magnet;
  }
} // namespace convert

//-------------------------------------------------------------------

ourtrack::ourtrack(QWidget *parent)
  : QMainWindow(parent)
{
  ui.setupUi(this);  

  // Соединяем сигналы с UI со слотами  
  QObject::connect(ui.ButtonFind, SIGNAL(clicked()), this, SLOT(SendFindQuery()));
  QObject::connect(ui.TableResult, SIGNAL(itemActivated(QTableWidgetItem *)), this, SLOT(ResultItemActivated(QTableWidgetItem *)));
  QObject::connect(ui.TableResult, SIGNAL(itemPressed(QTableWidgetItem *)), this, SLOT(ResultItemActivated(QTableWidgetItem *)));
  QObject::connect(ui.DescriptionBrowser, SIGNAL(linkClicked(const QUrl & )), this, SLOT(linkClickedDownload(const QUrl & )));

  ui.DescriptionBrowser->page()->setLinkDelegationPolicy( QWebPage::DelegateAllLinks );

  ui.DescriptionBrowser->setUrl(QUrl(PROMO_PAGE_URL));    // Страница приземления

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
  // Открываем файл с со списком доступных адресов серверов
  QFile hosts(SERVER_HOSTS_PATH);
  if(hosts.open(QIODevice::ReadWrite))
  {
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
  }

  // Если хосты не определены, то пускаем юзера в программу, но отключаем возможность соединения
  if (!avaible_hosts.size())
  {    
    QMessageBox::critical(this, "Внимание", QString("Не найдено ни одной записи %1").arg(SERVER_HOSTS_PATH));
    ui.ButtonFind->setEnabled(0);
    return false;
  }

  return true;
}

//-------------------------------------------------------------------
void ourtrack::ShowList()
{
  QTableWidget *table = ui.TableResult;
  if (!table) return;
  
  if (!items.size())
  {  
    QMessageBox::warning(this, "Внимание", "Ничего не найдено");
    return;
  }

  table->clear();
  table->setColumnCount(6);
  table->setRowCount(items.size());

  QStringList header_lst;
  header_lst << COL_HEADER;
  table->setHorizontalHeaderLabels(header_lst);

  for ( auto i = 0; i < items.size(); i++ )
  {
    #define NEW_ITEM_TABLE(num_row, num_col, new_widget_item, source_item)   QTableWidgetItem *new_widget_item = new QTableWidgetItem(source_item); \
                                                                             table->setItem(num_row, num_col, new_widget_item);
    
    NEW_ITEM_TABLE(i, 0, widget_id,     QString::number(items[i].id));
    NEW_ITEM_TABLE(i, 1, widget_cat,    QString::number(items[i].category));
    NEW_ITEM_TABLE(i, 2, widget_name,   items[i].name);
    NEW_ITEM_TABLE(i, 3, widget_size,   QString::number((long long)items[i].size));
    NEW_ITEM_TABLE(i, 4, widget_rtime,  items[i].reg_time);
    NEW_ITEM_TABLE(i, 5, widget_liked,  QString::number(items[i].liked));
  }
  
  table->resizeColumnsToContents();
}

//-------------------------------------------------------------------

void ourtrack::ResultItemActivated(QTableWidgetItem *item)
{
  ui.DescriptionBrowser->setHtml(GetDescHtml(item->row()));
}

//-------------------------------------------------------------------

QString ourtrack::GetDescHtml(const int num)
{
  MainListItem *MainItem = &items[num];

  QString html;

  // Заголовок
  html += QString("<h3>%1</h3><hr>").arg(MainItem->name);

  // Описание
  html += MainItem->description;

  // Ссылка
  html += QString("<a href='%1'>Скачать</a> ").arg(convert::magnetUrl(MainItem->hash,
                                                                      MainItem->name,
                                                                      MainItem->size,
                                                                      false));
  
  // Размер и дата
  html += QString("(Размер: %1 МБ").arg(MainItem->size);

  // Описание
  html += QString("<br>%1").arg(MainItem->description);

  return html;
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
    QString msg = "Минимальная длина поискового запроса - " + QString::number(MIN_CHAR_SEARCH) + " символа(ов)";
    QMessageBox::warning(this, "Внимание", msg);
    return;
  }

  QByteArray sbuf(search_query.toStdString().c_str());

  // Соединяемся с сервером
  connect_to_host:
  host_info server_addr = GetRandomHost();
  socket->connectToHost(server_addr.host, server_addr.port);
  if (!socket->waitForConnected(TIME_WAIT_FOR_CONNECT))
  {
    QMessageBox::warning(this, "Внимание", "Превышено время ожидания соединения");

    // Соединиться с другим сервером?
    if ( QMessageBox::question(this, "Переподключиться?", "Попробовать еще с другим сервером?",
                               QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes)
    {
      goto connect_to_host;
    }

    socket->close();
    return;
  }  

  // Отправляем наш поисковый запрос
  socket->write(sbuf);
  if (!socket->waitForBytesWritten(TIME_WAIT_FOR_WRITTEN))
  {        
    QMessageBox::warning(this, "Внимание", "Превышено время ожидания отправки поискового запроса");
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

void ourtrack::linkClickedDownload(const QUrl& url)
{  
  QDesktopServices::openUrl(url);
  return;
}

//-------------------------------------------------------------------