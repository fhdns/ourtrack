#include "databasecontrol.h"
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QRegularExpression>
#include <QDebug>

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
  QString strQuery = QString("SELECT * from torrents \
                              WHERE name LIKE '%" + QRegularExpression::escape(search_query) + "%' \
                              LIMIT " + QString::number(QUERY_LIMIT));

  if (!query.exec(strQuery))
  {
    qDebug() << "Unable to select";
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
