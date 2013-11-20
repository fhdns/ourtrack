 #include "bencodeparser.h"
 #include "metainfo.h"

 #include <QDateTime>
 #include <QMetaType>
 #include <QString>
 #include <QByteArray>
 #include <QMap>
 #include <QVariant>
 #include <QList>
 #include <QtDebug>

 MetaInfo::MetaInfo()
 {
     clear();
 }

 void MetaInfo::clear()
 {
     errString = "Unknown error";
     content.clear();
     infoData.clear();
     metaInfoMultiFiles.clear();
 }

 bool MetaInfo::parse(const QByteArray &data)
 {
     clear();
     content = data;

     BencodeParser parser;
     if (!parser.parse(content)) {
         errString = parser.errorString();
         return false;
     }

     infoData = parser.infoSection();

     QMap<QByteArray, QVariant> dict = parser.dictionary();
     if (!dict.contains("info"))
         return false;

	 QMap<QByteArray, QVariant> info = dict.value("info").value<Dictionary>();

     if (info.contains("files")) {
         metaInfoFileForm = MultiFileForm;

         QList<QVariant> files = info.value("files").toList();

         for (int i = 0; i < files.size(); ++i) {
			 QMap<QByteArray, QVariant> file = files.at(i).value<Dictionary>();
             QList<QVariant> pathElements = file.value("path").toList();
             QByteArray path;
             foreach (QVariant p, pathElements) {
                 if (!path.isEmpty())
                     path += "/";
                 path += p.toByteArray();
             }

             MetaInfoMultiFile multiFile;
             multiFile.length = file.value("length").toLongLong();
             metaInfoMultiFiles << multiFile;
         }

     } else if (info.contains("length")) {
         metaInfoFileForm = SingleFileForm;
         metaInfoSingleFile.length = info.value("length").toLongLong();
     }

     return true;
 }

 QByteArray MetaInfo::infoValue() const
 {
     return infoData;
 }

 MetaInfo::FileForm MetaInfo::fileForm() const
 {
     return metaInfoFileForm;
 }

 MetaInfoSingleFile MetaInfo::singleFile() const
 {
     return metaInfoSingleFile;
 }

 QList<MetaInfoMultiFile> MetaInfo::multiFiles() const
 {
     return metaInfoMultiFiles;
 }

 qint64 MetaInfo::totalSize() const
 {
     if (fileForm() == SingleFileForm)
         return singleFile().length;

     qint64 size = 0;
     foreach (MetaInfoMultiFile file, multiFiles())
         size += file.length;
     return size;
 }
