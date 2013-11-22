#include "ourtrack.h"
#include "convert.h"
#include <QFile>
#include <QList>
#include <QStringList>
#include <QDesktopServices>
#include <QFileDialog>


void ourtrack::AddTorrent()
{
  // Get info from form
  MainListItem itm;
  if (!AddFormToListItem(itm))
    return;
  
  QVector<MainListItem> items;
  items.push_back(itm);

  QByteArray sbuff = Serialize(items);

  // Send
  if (!conn.Send(&sbuff, FLAG_ADD))
  {
    QMessageBox::critical(0, tr("Error"), tr("Torrent wasn't sent to server"));
    return;
  }

  if (QMessageBox::warning(0, tr("Added"),
                           tr("Torrent has been sent to the server and will be available after being moderated\n\r\
                           Add another torrent?"), QMessageBox::Yes|QMessageBox::No) == QMessageBox::No)
  {
    add_form->close();
  }
}

bool ourtrack::AddFormToListItem(MainListItem &result)
{
  result.name         = ui_add.EditName->text();
  result.category     = ui_add.CBoxCategory->currentIndex();
  result.description  = ui_add.EditDescription->document()->toPlainText();
  result.hash         = ui_add.EditHash->text();
  result.size         = ui_add.EditSize->text().toInt();

  // Check
  if (result.name.length() < 10)
  {
    QMessageBox::warning(0, tr("Attention!"), tr("Minimum field size 'Name' 10 symbols"));
    ui_add.EditName->setFocus();
    return false;
  }
  if (!result.category)
  {
    QMessageBox::warning(0, tr("Attention!"), tr("Select a category"));
    ui_add.CBoxCategory->showPopup();
    return false;
  }
  if (result.description.length() < 100)
  {
    QMessageBox::warning(0, tr("Attention!"), tr("Minimum field size 'Description' 100 symbols"));
    ui_add.EditDescription->setFocus();
    return false;
  }
  if (!result.hash.length())
  {
    QMessageBox::warning(0, tr("Attention!"), tr("Hash is not entered"));
    ui_add.EditHash->setFocus();
    return false;
  }
  if (!result.size)
  {
    QMessageBox::warning(0, tr("Attention!"), tr("Uncorrect file size"));
    ui_add.EditSize->setFocus();
    return false;
  }

  return true;
}

//-------------------------------------------------------------------

bool ourtrack::TemplateLoad()
{
  QLineEdit *name = ui_add.EditName;
  QTextEdit *desc = ui_add.EditDescription;
  QString filename;

  QObject *snd = sender();
  if (snd == ui_add.ButtonVideoTemplate)
  {
    filename = "video.html";
    ui_add.CBoxCategory->setCurrentIndex(categories.indexOf(tr("Video")));
  }
  else if (snd == ui_add.ButtonAudioTemplate)
  {
    filename = "audio.html";
    ui_add.CBoxCategory->setCurrentIndex(categories.indexOf(tr("Audio")));
  }
  else if (snd == ui_add.ButtonGameTemplate)
  {
    filename = "game.html";
    ui_add.CBoxCategory->setCurrentIndex(categories.indexOf(tr("Games")));
  }
  else if (snd == ui_add.ButtonSoftTemplate)
  {
    filename = "soft.html";
    ui_add.CBoxCategory->setCurrentIndex(categories.indexOf(tr("Soft")));
  }

  QFile f(TEMPLATE_PATH + filename);
  if (!f.open(QIODevice::ReadOnly))
  {
    return false;
  }
  name->setText(f.readLine());
  desc->setPlainText(f.readAll());
  //desc->setPlainText
  return true;

}

//-------------------------------------------------------------------

void ourtrack::OpenDialogTorrent()
{  
	QString fileName = QFileDialog::getOpenFileName(0, tr("Select torrent file"),
                                                     "",
                                                     tr("Torrents (*.torrent);; All files (*.*)"),
                                                     0,
                                                     QFileDialog::DontUseNativeDialog);
     if (fileName.isEmpty())
         return;

   QByteArray hash;
   quint64 filelen;
   getTorrentInfo(fileName, hash, filelen);
   
   ui_add.EditPathTorrent->setText(fileName);
   ui_add.EditSize->setText(QString::number(filelen));
   ui_add.EditHash->setText(hash);
}

void ourtrack::getTorrentInfo(const QString &torrentFile, QByteArray &infoHash, quint64 &filesLen)
{
  MetaInfo metaInfo;
  QFile torrent(torrentFile);
  if (!torrent.open(QFile::ReadOnly) || !metaInfo.parse(torrent.readAll())) 
    return;

  QByteArray infoValue = metaInfo.infoValue();
  infoHash = QCryptographicHash::hash(infoValue, QCryptographicHash::Sha1);
  convert::boolBase32Encode(infoHash);

  filesLen = metaInfo.totalSize();
}

//-------------------------------------------------------------------
