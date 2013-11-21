#include <QFile>
#include <QList>
#include <QStringList>
#include <QDesktopServices>
#include <QFileDialog>
#include "ourtrack.h"
#include "convert.h"

//-------------------------------------------------------------------

ourtrack::ourtrack(QWidget *parent)
  : QMainWindow(parent)
{
  // Установка UI
  ui_main.setupUi(this); 

  // Идентифицируем список категорий
  categories << DEFAULT_CATEGORIES;  

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

  // Запрашиваем список последних торрентов  
  GetLastTorrent();
}

//-------------------------------------------------------------------

ourtrack::~ourtrack()
{
}

//-------------------------------------------------------------------

void ourtrack::ShowList()
{
  statusBar()->showMessage(tr("Выводим результат"));
  

  QTableWidget *table = ui_main.TableResult;
  if (!table)
  {
      return;
  }  

  if (!items.size())
  {  
    table->clearContents();
    table->setRowCount(0);
    QMessageBox::warning(0, tr("Внимание"), tr("Ничего не найдено"));
    statusBar()->showMessage(tr("Готово"));
    return;
  }
  
  table->clear();
  table->setColumnCount(7);
  table->setRowCount(items.size());

  QStringList header_lst;
  header_lst << COL_HEADER;
  table->setHorizontalHeaderLabels(header_lst);

  for ( auto i = 0; i < items.size(); i++ )
  {
    #define NEW_ITEM_TABLE(num_row, num_col, new_widget_item, source_item, itm_icon)   QTableWidgetItem *new_widget_item = new QTableWidgetItem(source_item); \
                                                                                       table->setItem(num_row, num_col, new_widget_item); \
                                                                                       new_widget_item->setIcon(QIcon(itm_icon));
    
    NEW_ITEM_TABLE(i, 0, widget_id,     QString::number(items[i].id), ":/ourtrack/key.png");
    NEW_ITEM_TABLE(i, 1, widget_cat,    categories[items[i].category], "");
    NEW_ITEM_TABLE(i, 2, widget_name,   items[i].name, ":/ourtrack/discription_icon.gif");
    NEW_ITEM_TABLE(i, 3, widget_size,   QString("%1 MB").arg(convert::ByteToMbyte(items[i].size)), "");
    NEW_ITEM_TABLE(i, 4, widget_rtime,  items[i].reg_time, "");
    NEW_ITEM_TABLE(i, 5, widget_downl,  QString::number(items[i].download), ":/ourtrack/download.png");
    NEW_ITEM_TABLE(i, 6, widget_liked,  QString::number(items[i].liked), ":/ourtrack/like-icon.png");
  }

  table->resizeColumnsToContents();
  // Устанавливаем ограничение для Name column
  table->setColumnWidth(0, 0);
  table->setColumnWidth(2, 300);
  QApplication::alert(this);
  statusBar()->showMessage(tr("Готово"));
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
  in << "Размер: " + QString::number(convert::ByteToMbyte(MainItem->size)) + " МБ; ";

  // Дата
  in << "Дата: " + MainItem->reg_time + "; ";
  
  // Описание
  in << "<hr><br>" << MainItem->description;

  return html;
}

//-------------------------------------------------------------------

void ourtrack::SendFindQuery()
{
  statusBar()->showMessage(tr("Соединение..."));
  // Забираем запрос с формы
  QString search_query = ui_main.EditFind->text();
  // Убираем лишние пробелы
  search_query.replace("  ", " ");

  // Если запрос меньше требуемого размера, говорим ему об этом
  if (search_query.length() < MIN_CHAR_SEARCH)
  {    
    QString msg = tr("Минимальная длина поискового запроса - ") + QString::number(MIN_CHAR_SEARCH) + tr(" символа(ов)");
    QMessageBox::warning(0, tr("Внимание"), msg);
    return;
  }

  // Отправляем на сервер
  QByteArray tmp = search_query.toUtf8();
  conn.Send(&tmp, FLAG_FIND);
  statusBar()->showMessage(tr("Ожидание ответа от сервера..."), 10000);
}

//-------------------------------------------------------------------

void ourtrack::linkClickedDownload(const QUrl& url)
{
    QDesktopServices::openUrl(url);
}

//-------------------------------------------------------------------

void ourtrack::AddTorrentFormOpen()
{  
  // Инициализация формы добавления  
  add_form = new QWidget;
  ui_add.setupUi(add_form);  
  ui_add.CBoxCategory->addItems(categories);

  // Соединяем сигналы формы добавления со слотами
  QObject::connect(ui_add.ButtonAddTorrent, SIGNAL(clicked()), this, SLOT(AddTorrent()));
  QObject::connect(ui_add.ButtonCancel, SIGNAL(clicked()), add_form, SLOT(close())); 
  
  QObject::connect(ui_add.ButtonVideoTemplate, SIGNAL(clicked()), this, SLOT(TemplateLoad()));
  QObject::connect(ui_add.ButtonAudioTemplate, SIGNAL(clicked()), this, SLOT(TemplateLoad()));
  QObject::connect(ui_add.ButtonGameTemplate, SIGNAL(clicked()), this, SLOT(TemplateLoad()));
  QObject::connect(ui_add.ButtonSoftTemplate, SIGNAL(clicked()), this, SLOT(TemplateLoad()));
  
  QObject::connect(ui_add.ButtonOpenDialogTorrent, SIGNAL(clicked()), this, SLOT(OpenDialogTorrent()));

  add_form->show();
  add_form->setAttribute(Qt::WA_DeleteOnClose);
}

//-------------------------------------------------------------------

void ourtrack::GetLastTorrent()
{
  QByteArray mgs("getlast");
  conn.Send(&mgs, FLAG_LAST);
}

//-------------------------------------------------------------------

void ourtrack::DissectServerAnswer(QByteArray *data)
{
  // Сериализуем в вектор
  DeSerialize(*data);
  // Выводим
  ShowList();
}
//-------------------------------------------------------------------
