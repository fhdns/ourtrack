#include "ourtrackserv.h"

//-------------------------------------------------------------------

QByteArray ourtrackserv::Serialize(QVector<MainListItem> &items)
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
    for (int j = 0; j < COL_COUNT; j++)
      m.insert(counter++, it->Data[j]);

  out << m;
  return buffer;
}

//-------------------------------------------------------------------