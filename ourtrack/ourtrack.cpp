#include "ourtrack.h"

ourtrack::ourtrack(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);    
    QObject::connect(ui.ButtonFind, SIGNAL(clicked()), this, SLOT(GetFindResult()));
}

ourtrack::~ourtrack()
{
}

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

void ourtrack::GetFindResult()
{
  QString search_query = SERVICE_MESSAGE_FIND + ui.EditFind->text();
  QString host = "localhost";
  qint16 port = 7777;
  
  QTcpSocket *socket;
  socket = new QTcpSocket(this);
  //connect(socket,SIGNAL(readyRead()),this, SLOT(slotReadServer()));
  
  socket->connectToHost(host, port);
  if (!socket->waitForConnected())
  {
    return;
  }

  // Отправляем запрос
  //socket->write(search_query->toLatin1(), search_query->length());
  // ждем
  socket->close();

  //socket->write("abc", 3);

  //char *c = new char[3];
  //forever
  //{
  //  quint64 numRead  = socket->read(c, 3);

  //  // сделать что-то с массивом

  //  if (numRead == 0 )//&& !socket->waitForReadyRead())
  //    break;
  //}

  //socket->close();
  //delete socket;

  // Выводим таблицу
  ShowList();
}

void ourtrack::slotReadServer()
{
  QString *search_query = &ui.EditFind->text();
  QTcpSocket* socket = (QTcpSocket*)sender();

  // Пример отправки ответа клиенту
  QTextStream os(socket);
  os.setAutoDetectUnicode(true);
  os << search_query;

  qDebug() << socket->readAll() + "\n\r";

  socket->close();
}

char *ourtrack::ItemsSerialization(UINT &len)
{
  len = sizeof(items);
  char *buff = new char[len];
  memcpy_s(buff, len, &items, len);
  return buff;
}

void ourtrack::ItemsDeSerialization(const char *buff, const UINT len)
{
  memcpy_s(&items, len, buff, len);
}