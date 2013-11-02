#include "convert.h"
#include <QUrl>
#include <QStringList>

//-------------------------------------------------------------------

QStringList convert::default_trackers()
{
  QStringList list;
  list << "http://retracker.local/announce";
  list << "udp://tracker.openbittorrent.com:80/announce";
  list << "udp://tracker.publicbt.com:80/announce";
  list << "udp://tracker.ccc.de:80/announce";
  return list;
}

//-------------------------------------------------------------------

QString convert::magnetUrl(QString hash, QString name, qlonglong size, bool urlencode)
{
  QString magnet = "magnet:?xt=urn:btih:" + hash +
    "&dn=" + (urlencode ? QUrl::toPercentEncoding(name) : name) +
    "&xl=" + QString::number(size);
  QStringList trackers_list = default_trackers();
  foreach (QString tracker, trackers_list)
  {
    if (!tracker.isEmpty())
    {
      magnet += "&tr=" + (urlencode ? QUrl::toPercentEncoding(tracker) : tracker);
    }
  }
  return magnet;
}

//-------------------------------------------------------------------
