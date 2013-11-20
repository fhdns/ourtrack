#include "ourtrackserv.h"

//-------------------------------------------------------------------

QByteArray ourtrackserv::Serialize(const QVector<MainListItem> &items)
{
  // Результирующий буффер
  QByteArray buffer;
  QDataStream out(&buffer, QIODevice::WriteOnly);

  QMap<quint16, QVariant> m;  // Карта для записи элементов класса для последующей сериализации
  int counter = 0;            // Количество записей в карту (используется как ключ)

  // Добавляем количество элементов (потребуется для десериализации)
  m.insert(counter++, items.size());

  // Добавляем все элементы
  for (auto it = items.begin(); it != items.end(); ++it)
  {
    m.insert(counter++, it->id);
    m.insert(counter++, it->category);
    m.insert(counter++, it->name);
    m.insert(counter++, it->description);
    m.insert(counter++, it->size);
    m.insert(counter++, it->reg_time);
    m.insert(counter++, it->hash);
    m.insert(counter++, it->user_id);
    m.insert(counter++, it->download);
    m.insert(counter++, it->liked);
  }

  out << m;
  return  qCompress(buffer, 0);
}

//-------------------------------------------------------------------

QVector<MainListItem> ourtrackserv::DeSerialize(const QByteArray &buffer)
{
  QVector<MainListItem> items;

  QByteArray uncompr_buffer = qUncompress(buffer);

  QDataStream in(&uncompr_buffer, QIODevice::ReadOnly);

  QMap<quint16, QVariant> m;  // Карта для записи элементов класса
  int counter = 0;            // Количество записей в карту (используется как ключ)

  // Заполняем карту
  in >> m;

  // Забираем количество элементов
  int count = m.value(counter++).toInt();

  // Добавляем все элементы
  for (int i = 0; i < count; i++)
  {
    MainListItem item;
    item.id           = m.value(counter++).toInt();
    item.category     = m.value(counter++).toInt();
    item.name         = m.value(counter++).toString();
    item.description  = m.value(counter++).toString();
    item.size         = m.value(counter++).toLongLong();
    item.reg_time     = m.value(counter++).toString();
    item.hash         = m.value(counter++).toString();
    item.user_id      = m.value(counter++).toInt();
    item.download     = m.value(counter++).toInt();
    item.liked        = m.value(counter++).toInt();
    items.push_back(item);
  }
  return items;
}

//-------------------------------------------------------------------