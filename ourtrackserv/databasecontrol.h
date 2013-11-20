#ifndef DATABASECONTROL_H
#define DATABASECONTROL_H

//-------------------------------------------------------------------

#include <QObject>
#include <QVector>
#include <QtSql/QSqlDatabase>

#include "globalsettings.h"
#include <mainlistitem.h>

//-------------------------------------------------------------------

class DatabaseControl : public QObject
{
  Q_OBJECT

public:
    DatabaseControl(QObject *parent = 0);
    ~DatabaseControl();

    // Управление БД
    void connect_db();
    void disconnect_db();

    // Действия с БД
    void GetFindResult(const QString &search_query, QVector<MainListItem> &result);
    void AddTorrentItem(const MainListItem &item);
    void LikedTorrent(long long id);
    void PlusDownloadTorrent(long long id);
    void GetLastResult(QVector<MainListItem> &result);

private:
    QSqlDatabase db;
};

//-------------------------------------------------------------------

#endif // DATABASECONTROL_H
