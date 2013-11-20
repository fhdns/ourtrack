#include <QFile>
#include <QList>
#include <QMutex>
#include <QStringList>
#include <QDesktopServices>
#include "ourtrack.h"
#include "convert.h"

//-------------------------------------------------------------------

ourtrack::ourtrack(QWidget *parent)
  : QMainWindow(parent)
{
  // Установка UI
  ui_main.setupUi(this);

  // Инициализация формы добавления  
  add_form = new QWidget;
  ui_add.setupUi(add_form);
  // Соединяем сигналы формы добавления со слотами
  QObject::connect(ui_add.ButtonAddTorrent, SIGNAL(clicked()), this, SLOT(AddTorrent()));
  QObject::connect(ui_add.ButtonCancel, SIGNAL(clicked()), this, SLOT(AddTorrentFormClose()));
  

  // При получении ответа от сервера, выводим на форму
  QObject::connect(&conn, SIGNAL(SignalReadFinish(QByteArray*)), this, SLOT(DissectServerAnswer(QByteArray*)));

  // Соединяем сигналы основного UI со слотами
  QObject::connect(ui_main.ButtonFind, SIGNAL(clicked()), this, SLOT(SendFindQuery()));
  QObject::connect(ui_main.TableResult, SIGNAL(itemActivated(QTableWidgetItem *)), this, SLOT(ResultItemActivated(QTableWidgetItem *)));
  QObject::connect(ui_main.TableResult, SIGNAL(itemPressed(QTableWidgetItem *)), this, SLOT(ResultItemActivated(QTableWidgetItem *)));
  QObject::connect(ui_main.DescriptionBrowser, SIGNAL(linkClicked(const QUrl & )), this, SLOT(linkClickedDownload(const QUrl & )));
  // Меню
  QObject::connect(ui_main.ActionAddTorrent, SIGNAL(triggered()), this, SLOT(AddTorrentFormOpen()));
  QObject::connect(ui_main.ActionGetLast, SIGNAL(triggered()), this, SLOT(GetLastTorrent()));

  // Настройка WebView
  ui_main.DescriptionBrowser->page()->setLinkDelegationPolicy( QWebPage::DelegateAllLinks );
  ui_main.DescriptionBrowser->setUrl(QUrl(PROMO_PAGE_URL));    // Страница приземления
}

//-------------------------------------------------------------------

ourtrack::~ourtrack()
{
  delete add_form;
}

//-------------------------------------------------------------------

void ourtrack::ShowList()
{
  QTableWidget *table = ui_main.TableResult;
  if (!table)
  {
      return;
  }  

  if (!items.size())
  {  
    table->clearContents();
    table->setRowCount(0);
    QMessageBox::warning(0, "Внимание", "Ничего не найдено");
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
    NEW_ITEM_TABLE(i, 3, widget_size,   QString::number(items[i].size));
    NEW_ITEM_TABLE(i, 4, widget_rtime,  items[i].reg_time);
    NEW_ITEM_TABLE(i, 5, widget_liked,  QString::number(items[i].liked));
  }

  table->resizeColumnsToContents(); 
}

//-------------------------------------------------------------------

void ourtrack::ResultItemActivated(QTableWidgetItem *item)
{
  ui_main.DescriptionBrowser->setHtml(GetDescHtml(item->row()));
}

//-------------------------------------------------------------------

QString ourtrack::GetDescHtml(const int num)
{
  MainListItem *MainItem = &items[num];

  QString html;
  QTextStream in(&html);

  // Заголовок
  in << "<h3>" << MainItem->name << "</h3><hr>";  

  // Ссылка
  in << QString("<a href='%1'>Скачать</a>; ").arg(convert::magnetUrl(MainItem->hash,
                                                                   MainItem->name,
                                                                   MainItem->size,
                                                                   false));
  // Размер
  in << "Размер: " + QString::number(MainItem->size/(1024.00 * 1024.00)) + " МБ; ";

  // Дата
  in << "Дата: " + MainItem->reg_time + "; ";
  
  // Дата
  in << "Рейтинг: +" + QString::number(MainItem->liked) + "; ";

  // Описание
  in << "<hr><br>" << MainItem->description;

  return html;
}

//-------------------------------------------------------------------

void ourtrack::SendFindQuery()
{
  // Забираем запрос с формы
  QString search_query = ui_main.EditFind->text();
  // Убираем лишние пробелы
  search_query.replace("  ", " ");

  // Если запрос меньше требуемого размера, говорим ему об этом
  if (search_query.length() < MIN_CHAR_SEARCH)
  {    
    QString msg = "Минимальная длина поискового запроса - " + QString::number(MIN_CHAR_SEARCH) + " символа(ов)";
    QMessageBox::warning(0, "Внимание", msg);
    return;
  }

  // Отправляем на сервер
  conn.Send(&search_query.toUtf8());
}

//-------------------------------------------------------------------

void ourtrack::linkClickedDownload(const QUrl& url)
{  
  QDesktopServices::openUrl(url);
  return;
}

//-------------------------------------------------------------------

void ourtrack::AddTorrentFormOpen()
{
  add_form->show();
}

void ourtrack::AddTorrentFormClose()
{
  add_form->close();
}

//-------------------------------------------------------------------

void ourtrack::AddTorrent()
{
  // Добавление торрента
  QVector<MainListItem> items;
  // Собираем информацию с формы
  items.push_back(AddFormToListItem());
  // Сериализуем
  QByteArray sbuff = Serialize(items);
  // Отправляем на сервер
  conn.Send(&sbuff, FLAG_ADD);
}

//-------------------------------------------------------------------

void ourtrack::GetLastTorrent()
{
  QByteArray mgs("getlast");
  conn.Send(&mgs, 0x03);
}

//-------------------------------------------------------------------

void ourtrack::DissectServerAnswer(QByteArray *data)
{
  // Первый байт - флаг
  // <!-- dissect first byte -->
  // Сериализуем в вектор
  DeSerialize(*data);
  // Выводим
  ShowList();
}

//-------------------------------------------------------------------

MainListItem ourtrack::AddFormToListItem()
{
  MainListItem result;
  result.name         = ui_add.EditName->text();
  result.category     = ui_add.EditCategory->text().toInt();
  result.description  = ui_add.EditDescription->document()->toHtml();
  result.hash         = ui_add.EditHash->text();
  result.size         = ui_add.EditSize->text().toInt();
  return result;
}

//-------------------------------------------------------------------