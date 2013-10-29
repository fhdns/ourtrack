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
    m.insert(counter++, it->liked);
  }

  out << m;
  return  qCompress(buffer, 0);
}

//-------------------------------------------------------------------