#include <QObject>

//-------------------------------------------------------------------

namespace convert
{
  QStringList   default_trackers();
  QString       magnetUrl(QString hash, QString name, qlonglong size, bool urlencode);
} // namespace convert

//-------------------------------------------------------------------