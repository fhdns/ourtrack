#include "databasecontrol.h"
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QRegularExpression>
#include <QDebug>
#include <QDateTime>

//-------------------------------------------------------------------

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
  query.prepare(QString("SELECT * from torrents \
                         WHERE name LIKE '%" + QRegularExpression::escape(search_query) + "%' \
                         LIMIT " + QString::number(QUERY_LIMIT)));

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
    item.reg_time     = query.value(rec.indexOf("size")).toFloat();
    item.reg_time     = query.value(rec.indexOf("reg_time")).toString();
    item.hash         = query.value(rec.indexOf("hash")).toString();
    item.user_id      = query.value(rec.indexOf("user_id")).toInt();
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
    
  QSqlQuery query(db);

  query.prepare("INSERT INTO `torrents_temp` \
                (category, name, description, size, reg_time, hash, user_id, liked) \
                VALUES (:c,:n,:d,:s,:r,:h,:u,:l);");

  #define ESCAPE(str) QRegularExpression::escape(str)

  query.bindValue(":c", item.category);
  query.bindValue(":n", ESCAPE(item.name));
  query.bindValue(":d", ESCAPE(item.description));
  query.bindValue(":s", item.size);
  query.bindValue(":r", "now");
  query.bindValue(":h", item.hash);
  query.bindValue(":u", item.user_id);
  query.bindValue(":l", 0);

  if (!query.exec())
  {
    qDebug() << "Unable to insert: " << query.lastError();    
    return;
  }
}

//-------------------------------------------------------------------

void DatabaseControl::LikedTorrent(int id)
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
    item.reg_time     = query.value(rec.indexOf("size")).toFloat();
    item.reg_time     = query.value(rec.indexOf("reg_time")).toString();
    item.hash         = query.value(rec.indexOf("hash")).toString();
    item.user_id      = query.value(rec.indexOf("user_id")).toInt();
    item.liked        = query.value(rec.indexOf("liked")).toInt();
    result.push_back(item);
  }
}

//-------------------------------------------------------------------