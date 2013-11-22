#include "ourtrack.h"

//-------------------------------------------------------------------

QByteArray ourtrack::Serialize(const QVector<MainListItem> &items)
{
  // Result buffer
  QByteArray buffer;
  QDataStream out(&buffer, QIODevice::WriteOnly);

  QMap<quint16, QVariant> m;
  int counter = 0;

  m.insert(counter++, items.size());

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

void ourtrack::DeSerialize(const QByteArray &buffer)
{
  items.clear();

  QByteArray uncompr_buffer = qUncompress(buffer);

  QDataStream in(&uncompr_buffer, QIODevice::ReadOnly);

  QMap<quint16, QVariant> m;
  int counter = 0;

  in >> m;

  int count = m.value(counter++).toInt();
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
}
//-------------------------------------------------------------------