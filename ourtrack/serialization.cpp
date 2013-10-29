#include "ourtrack.h"

//-------------------------------------------------------------------

void ourtrack::DeSerialize(const QByteArray &buffer)
{
  // Очищаем существующий вектор элементов поисковой выдачи
  items.clear();

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
    item.size         = m.value(counter++).toFloat();
    item.reg_time     = m.value(counter++).toString();
    item.hash         = m.value(counter++).toString();
    item.user_id      = m.value(counter++).toInt();
    item.liked        = m.value(counter++).toInt();
    items.push_back(item);
  }
}

//-------------------------------------------------------------------