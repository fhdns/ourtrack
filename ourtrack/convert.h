#include <QObject>

//-------------------------------------------------------------------

namespace convert
{
  QStringList   default_trackers();
  QString       magnetUrl(QString hash, QString name, qlonglong size, bool urlencode);
  float         ByteToMbyte(long long byte);
  
  QByteArray base32Encode(uchar *input, int inputLength);
  bool boolBase32Encode(QByteArray &data);
} // namespace convert

//-------------------------------------------------------------------

struct Base32
{
	static bool Encode32(unsigned char* in, int inLen, unsigned char* out);
	static int  GetEncode32Length(int bytes);
	static bool Map32(unsigned char* inout32, int inout32Len, unsigned char* alpha32);
};