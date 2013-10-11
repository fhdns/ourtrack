#include "ourtrack.h"

//-------------------------------------------------------------------

QByteArray ourtrack::Serialize()
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

void ourtrack::DeSerialize(QByteArray &buffer)
{
  // Очищаем существующий вектор элементов поисковой выдачи
  items.clear();

  QDataStream in(&buffer, QIODevice::ReadOnly);

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
    for (int j = 0; j < COL_COUNT; j++)
    {
      item.Data[j] = m.value(counter++).toString();
    }
    items.push_back(item);
  }
}

//-------------------------------------------------------------------