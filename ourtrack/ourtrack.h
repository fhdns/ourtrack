#ifndef OURTRACK_H
#define OURTRACK_H

//-------------------------------------------------------------------

#include <QObject>
#include <QVector>
#include <QMessageBox>
#include <QTableWidgetItem>

#include "ui_ourtrack.h"
#include "proxyserver.h"
#include "mainlistitem.h"

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
  // Взаимодействие с сервером
  void SendFindQuery();
  void ReadServer();

private:
  
  // Список элементов поисковой выдачи
  QVector<MainListItem> items;
  
  // Пользовательский интерфейс
  Ui::ourtrackClass     ui;

  // Работа с сетью
  QTcpSocket            *socket;
  ProxyServer           *proxy_srv;   // Модуль работы с прокс-сервером
  
  // Подключение к серверу
  // Доступные адреса расположения сервера (из файла SERVER_HOSTS_PATH)
  struct host_info
  {
    QString host;
    quint64 port;
  };
  QVector<host_info> avaible_hosts;

  // Методы  
  bool      ConfLoad();                                 // Загрузка конфигурации
  QString   GetDescHtml(const int num);                 // Генерация html из элемента вектора по номеру
  void      ShowList();                                 // Вывод вектора поисковой выдачи в tableView
  void      DeSerialize(const QByteArray &buffer);      // Десериализация предметов списка
  host_info GetRandomHost();                            // Выбирает случайный адрес из списка hosts.ini
};
    
//-------------------------------------------------------------------
#endif // OURTRACK_H
