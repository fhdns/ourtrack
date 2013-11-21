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

float convert::ByteToMbyte(long long byte)
{
  //1024 * 1024 = 1048576
  return (float)byte/1048576.00;
}

//-------------------------------------------------------------------

// BASE32
QByteArray convert::base32Encode(uchar *input, int inputLength)
{
    static const char *base32Alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567"; //Used for Base32 conversions - RFC4648 standard

    int encodedLength = Base32::GetEncode32Length(inputLength);
    uchar *b32text = new uchar[encodedLength];
    if (!Base32::Encode32(input, inputLength, b32text))
    {
        return QByteArray();
    }

    char *alpha = new char[32];
    memcpy(alpha, base32Alpha, 32);
    Base32::Map32(b32text, encodedLength, (uchar *)alpha);

    QByteArray output((const char*)b32text, encodedLength);

    delete [] b32text;
    delete [] alpha;
    return output;
}

bool convert::boolBase32Encode(QByteArray &data)
{
    if (data.isEmpty())
        return false;

    QByteArray res = base32Encode((uchar *)data.data(), data.size());
    if (res.isEmpty())
        return false;

    data = res;
    return true;
}


int Base32::GetEncode32Length(int bytes)
{
   int bits = bytes * 8;
   int length = bits / 5;
   if((bits % 5) > 0)
   {
      length++;
   }
   return length;
}

static bool Encode32Block(unsigned char* in5, unsigned char* out8)
{
      // pack 5 bytes
      unsigned long long buffer = 0;
      for(int i = 0; i < 5; i++)
      {
		  if(i != 0)
		  {
			  buffer = (buffer << 8);
		  }
		  buffer = buffer | in5[i];
      }
      // output 8 bytes
      for(int j = 7; j >= 0; j--)
      {
		  buffer = buffer << (24 + (7 - j) * 5);
		  buffer = buffer >> (24 + (7 - j) * 5);
		  unsigned char c = (unsigned char)(buffer >> (j * 5));
		  // self check
		  if(c >= 32) return false;
		  out8[7 - j] = c;
      }
	  return true;
}

bool Base32::Encode32(unsigned char* in, int inLen, unsigned char* out)
{
   if((in == 0) || (inLen <= 0) || (out == 0)) return false;

   int d = inLen / 5;
   int r = inLen % 5;

   unsigned char outBuff[8];

   for(int j = 0; j < d; j++)
   {
      if(!Encode32Block(&in[j * 5], &outBuff[0])) return false;
      memmove(&out[j * 8], &outBuff[0], sizeof(unsigned char) * 8);
   }

   unsigned char padd[5];
   memset(padd, 0, sizeof(unsigned char) * 5);
   for(int i = 0; i < r; i++)
   {
      padd[i] = in[inLen - r + i];
   }
   if(!Encode32Block(&padd[0], &outBuff[0])) return false;
   memmove(&out[d * 8], &outBuff[0], sizeof(unsigned char) * GetEncode32Length(r));

   return true;
}

bool Base32::Map32(unsigned char* inout32, int inout32Len, unsigned char* alpha32)
{
	if((inout32 == 0) || (inout32Len <= 0) || (alpha32 == 0)) return false;
	for(int i = 0; i < inout32Len; i++)
	{
		if(inout32[i] >=32) return false;
		inout32[i] = alpha32[inout32[i]];
	}
	return true;
}
