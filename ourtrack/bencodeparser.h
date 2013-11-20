 #ifndef BENCODEPARSER_H
 #define BENCODEPARSER_H

 #include <QByteArray>
 #include <QMap>
 #include <QString>
 #include <QVariant>
 #include <QList>

 typedef QMap<QByteArray,QVariant> Dictionary;
 Q_DECLARE_METATYPE(Dictionary)

 class BencodeParser
 {
 public:
     BencodeParser();

     bool parse(const QByteArray &content);
     QString errorString() const;

     Dictionary dictionary() const;
     QByteArray infoSection() const;

 private:
     bool getByteString(QByteArray *byteString);
     bool getInteger(qint64 *integer);
     bool getList(QList<QVariant> *list);
     bool getDictionary(Dictionary *dictionary);

     Dictionary dictionaryValue;

     QString errString;
     QByteArray content;
     int index;

     int infoStart;
     int infoLength;
 };

 #endif
