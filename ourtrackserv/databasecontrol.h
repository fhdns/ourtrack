#ifndef DATABASECONTROL_H
#define DATABASECONTROL_H

#include <QVector>
#include <mainlistitem.h>
#include <QtSql\QSqlDatabase>

class DatabaseControl : public QObject
{
  Q_OBJECT

public:
    DatabaseControl(QObject *parent = 0);
    ~DatabaseControl();

    void connect_db();
    void disconnect_db();
    void GetFindResult(QString &search_query, QVector<MainListItem> &result);

private:
    QSqlDatabase db;
};

#endif // DATABASECONTROL_H
