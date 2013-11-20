 #ifndef METAINFO_H
 #define METAINFO_H

 #include <QByteArray>
 #include <QDateTime>
 #include <QList>
 #include <QMap>
 #include <QString>
 #include <QStringList>
 #include <QVariant>

 struct MetaInfoSingleFile
 {
     qint64 length;
 };

 struct MetaInfoMultiFile
 {
     qint64 length;
 };

 class MetaInfo
 {
 public:
     enum FileForm {
         SingleFileForm,
         MultiFileForm
     };

     MetaInfo();
     void clear();

     bool parse(const QByteArray &data);
     QString errorString() const;

     QByteArray infoValue() const;

     FileForm fileForm() const;
     MetaInfoSingleFile singleFile() const;
     QList<MetaInfoMultiFile> multiFiles() const;

     // Total size
     qint64 totalSize() const;

	 FileForm metaInfoFileForm;

 private:
     QString errString;
     QByteArray content;
     QByteArray infoData; 
     MetaInfoSingleFile metaInfoSingleFile;
     QList<MetaInfoMultiFile> metaInfoMultiFiles;
 };

 #endif
