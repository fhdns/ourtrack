#include "databasecontrol.h"
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QRegularExpression>
#include <QDebug>

DatabaseControl::DatabaseControl(QObject *parent)
  : QObject(parent)
{

}

DatabaseControl::~DatabaseControl()
{

}

void DatabaseControl::connect_db()
{
  db = QSqlDatabase::addDatabase(DB_DRIVER);

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
  
  qDebug() << DB_DRIVER<< "Database connected (" << DB_HOST << ":" << DB_PORT << ")";
  return;  
}

void DatabaseControl::disconnect_db()
{
  db.close();
  qDebug() << DB_DRIVER<< "Database disconnected";
}

void DatabaseControl::GetFindResult(const QString &search_query, QVector<MainListItem> &result)
{  
  result.clear();

  QSqlQuery query(db);
  QString tmpQuery = QString("SELECT * from torrents \
                              WHERE name LIKE '%" + QRegularExpression::escape(search_query) + "%' \
                              LIMIT " + QString::number(QUERY_LIMIT));

  if (!query.exec(tmpQuery))
  {
    qDebug() << "Unable to select";
  }
  
  QSqlRecord rec = query.record();
  while (query.next())
  {
    MainListItem item;
    item.Data[0]  = query.value(rec.indexOf("id")).toString();
    item.Data[1]  = query.value(rec.indexOf("category")).toString();
    item.Data[2]  = query.value(rec.indexOf("name")).toString();
    item.Data[3]  = query.value(rec.indexOf("description")).toString();
    item.Data[4]  = query.value(rec.indexOf("size")).toString();
    item.Data[5]  = query.value(rec.indexOf("reg_time")).toString();
    item.Data[6]  = query.value(rec.indexOf("hash")).toString();
    item.Data[7]  = query.value(rec.indexOf("user_id")).toString();
    item.Data[8]  = query.value(rec.indexOf("liked")).toString();
    result.push_back(item);
  }
}
