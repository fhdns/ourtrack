#ifndef OURTRACK_H
#define OURTRACK_H

//-------------------------------------------------------------------

#include <QObject>
#include <QVector>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QSharedPointer>

#include "ui_ourtrack.h"
#include "ui_addtorrent.h"
#include "mainlistitem.h"
#include "connection.h"
#include "metainfo.h"

//-------------------------------------------------------------------

static const char *base32Alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567"; //Used for Base32 conversions - RFC4648 standard

//-------------------------------------------------------------------

class ourtrack : public QMainWindow
{
  Q_OBJECT

public:
  ourtrack(QWidget *parent = 0);
  ~ourtrack();
  
public slots:
  // UI
  void ResultItemActivated(QTableWidgetItem *item);
  void linkClickedDownload(const QUrl&);
  bool TemplateLoad();
  void OpenDialogTorrent();
  void AddTorrentFormOpen();
  void AddTorrent();
  void GetLastTorrent();
  // Send to server
  void SendFindQuery();

  // Recv from server and dissect
  void DissectServerResponse(QByteArray *data);

private:
  
  // List elements search response
  QVector<MainListItem> items;
  // Category list
  QStringList           categories;
  
  // User Interface
  Ui::ourtrackClass     ui_main;
  Ui::addtorrentClass   ui_add;
  QWidget               *add_form;
  

  // Network
  Connection            conn;

  // Methods
  QString     GetDescHtml(const int num);                     // Generation html by id
  QByteArray  Serialize(const QVector<MainListItem> &items);  // Serialization
  void        DeSerialize(const QByteArray &buffer);          // Deserialization
  void        ShowList();                                     // Out vector (server response) to tableView
  bool        AddFormToListItem(MainListItem &result);        // Get info from add_form to MainListItem
  void        getTorrentInfo(const QString &torrentFile, QByteArray &infoHash, quint64 &filesLen);
};
    
//-------------------------------------------------------------------
#endif // OURTRACK_H
