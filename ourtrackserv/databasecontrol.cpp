#include "databasecontrol.h"
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QDebug>
#include <QDateTime>

//-------------------------------------------------------------------

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
#  include <QRegExp>
#else
#  include <QRegularExpression>
#endif

DatabaseControl::DatabaseControl(QObject *parent)
  : QObject(parent)
{
}

//-------------------------------------------------------------------

DatabaseControl::~DatabaseControl()
{
  disconnect_db();
}

//-------------------------------------------------------------------

void DatabaseControl::connect_db()
{
  db = QSqlDatabase::addDatabase(DB_DRIVER);

  if(db.isOpen())
  {
    qDebug() << "Database already open";
    return;
  }

  db.setDatabaseName(DB_NAME);
  db.setHostName(DB_HOST);
  db.setPort(DB_PORT);
  db.setUserName(DB_USER);
  db.setPassword(DB_PASS);

  if (!db.open())
  {    
    qDebug() << "Cannot open database: " << db.lastError();
    return;
  }
  
  qDebug() << DB_DRIVER << "Database connected (" << DB_HOST << ":" << DB_PORT << ")";
}

//-------------------------------------------------------------------

void DatabaseControl::disconnect_db()
{
  db.close();
  qDebug() << DB_DRIVER<< "Database disconnected";
}

//-------------------------------------------------------------------

void DatabaseControl::GetFindResult(const QString &search_query, QVector<MainListItem> &result)
{  
  if(!db.isOpen())
  {
    qDebug() << "Find error: Database is not open";
    return;
  }

  result.clear();
  QSqlQuery query(db);
  query.prepare("SELECT * FROM `torrents` WHERE MATCH (name) AGAINST (:search_query) LIMIT :limit;");
  query.bindValue(":search_query", search_query);
  query.bindValue(":limit", QUERY_LIMIT);

  if (!query.exec())
  {
    qDebug() << "Unable to select: " << query.lastError(); 
    return;
  }
  
  QSqlRecord rec = query.record();
  while (query.next())
  {
    MainListItem item;
    item.id           = query.value(rec.indexOf("id")).toInt();
    item.category     = query.value(rec.indexOf("category")).toInt();
    item.name         = query.value(rec.indexOf("name")).toString();
    item.description  = query.value(rec.indexOf("description")).toString();
    item.size         = query.value(rec.indexOf("size")).toLongLong();
    item.reg_time     = query.value(rec.indexOf("reg_time")).toDateTime().toString("yyyy-MM-dd hh:mm");
    item.hash         = query.value(rec.indexOf("hash")).toString();
    item.user_id      = query.value(rec.indexOf("user_id")).toInt();
    item.download     = query.value(rec.indexOf("download")).toInt();
    item.liked        = query.value(rec.indexOf("liked")).toInt();
    result.push_back(item);
  }
}

//-------------------------------------------------------------------

void DatabaseControl::AddTorrentItem(const MainListItem &item)
{
  if(!db.isOpen())
  {
    qDebug() << "Find error: Database is not open";
    return;
  }

  // Check
  if (item.name.length() < MIN_CHAR_ADD_NAME)
    return;
  if (item.description.length() < MIN_CHAR_ADD_DESC)
    return;
  if (!item.size)
    return;
  if (!item.hash.length())
    return;
    
  QSqlQuery query(db);

  query.prepare("INSERT INTO `torrents_temp` \
                (category, name, description, size, reg_time, hash, user_id, download, liked) \
                VALUES (:c,:n,:d,:s,:r,:h,:u, :d, :l);");

  query.bindValue(":c", item.category);
  query.bindValue(":n", item.name);
  query.bindValue(":d", item.description);
  query.bindValue(":s", item.size);
  query.bindValue(":r", QDateTime::currentDateTime().toString("dd-MMM-yy hh:mm"));
  query.bindValue(":h", item.hash);
  query.bindValue(":u", 0);
  query.bindValue(":d", 0);
  query.bindValue(":l", 0);


  if (!query.exec())
  {
    qDebug() << "Unable to insert: " << query.lastError();    
    return;
  }
}

//-------------------------------------------------------------------

void DatabaseControl::LikedTorrent(long long id)
{  
  if(!db.isOpen())
  {
    qDebug() << "Find error: Database is not open";
    return;
  }
    
  QSqlQuery query(db);
  query.prepare("UPDATE torrents SET liked = (liked + 1) WHERE id = :id");
  query.bindValue(":id", id);

  if (!query.exec())
  {
    qDebug() << "Unable to add liked: " << query.lastError(); 
    return;
  }
}

//-------------------------------------------------------------------

void DatabaseControl::PlusDownloadTorrent(long long id)
{  
  if(!db.isOpen())
  {
    qDebug() << "Find error: Database is not open";
    return;
  }
    
  QSqlQuery query(db);
  query.prepare("UPDATE torrents SET download = (download + 1) WHERE id = :id");
  query.bindValue(":id", id);

  if (!query.exec())
  {
    qDebug() << "Unable to add download: " << query.lastError(); 
    return;
  }
}

//-------------------------------------------------------------------

void DatabaseControl::GetLastResult(QVector<MainListItem> &result)
{
  if(!db.isOpen())
  {
    qDebug() << "Find error: Database is not open";
    return;
  }
  result.clear();

  QSqlQuery query(db);
  query.prepare(QString("SELECT * from last_torrents \
                         LIMIT " + QString::number(QUERY_LASTLIMIT)));

  if (!query.exec())
  {
    qDebug() << "Unable to select: " << query.lastError(); 
    return;
  }
  
  QSqlRecord rec = query.record();
  while (query.next())
  {
    MainListItem item;
    item.id           = query.value(rec.indexOf("id")).toInt();
    item.category     = query.value(rec.indexOf("category")).toInt();
    item.name         = query.value(rec.indexOf("name")).toString();
    item.description  = query.value(rec.indexOf("description")).toString();
    item.size         = query.value(rec.indexOf("size")).toLongLong();
    item.reg_time     = query.value(rec.indexOf("reg_time")).toDateTime().toString("yyyy-MM-dd hh:mm");
    item.hash         = query.value(rec.indexOf("hash")).toString();
    item.user_id      = query.value(rec.indexOf("user_id")).toInt();
    item.download     = query.value(rec.indexOf("download")).toInt();
    item.liked        = query.value(rec.indexOf("liked")).toInt();
    result.push_back(item);
  }
}

//-------------------------------------------------------------------
