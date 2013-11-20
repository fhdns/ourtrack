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
  // Взаимодействие с UI
  void ResultItemActivated(QTableWidgetItem *item);
  void linkClickedDownload(const QUrl&);
  bool TemplateLoad();     // Загружаем шаблон новых торрентов
  void OpenDialogTorrent(); // Выбор торрент файла
  void AddTorrentFormOpen();
  void AddTorrent();
  void GetLastTorrent();
  // Взаимодействие с сервером
  void SendFindQuery();

  // Разбор ответа от сервера
  void DissectServerAnswer(QByteArray *data);

private:
  
  // Список элементов поисковой выдачи
  QVector<MainListItem> items;
  // Список категорий
  QStringList           categories;
  
  // Пользовательский интерфейс
  Ui::ourtrackClass     ui_main;
  Ui::addtorrentClass   ui_add;
  QWidget               *add_form;
  

  // Работа с сетью
  Connection            conn;

  // Методы
  QString     GetDescHtml(const int num);                     // Генерация html из элемента вектора по номеру
  QByteArray  Serialize(const QVector<MainListItem> &items);  // Сериализация предметов списка
  void        DeSerialize(const QByteArray &buffer);          // Десериализация предметов списка
  void        ShowList();                                     // Вывод вектора поисковой выдачи в tableView
  bool        AddFormToListItem(MainListItem &result);        // Собираем информацию с формы добавления
  void        getTorrentInfo(const QString &torrentFile, QByteArray &infoHash, quint64 &filesLen);
};
    
//-------------------------------------------------------------------
#endif // OURTRACK_H
