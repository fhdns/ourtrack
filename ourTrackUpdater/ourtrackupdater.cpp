#include "ourtrackupdater.h"

ourTrackUpdater::ourTrackUpdater(QWidget *parent)
	: QMainWindow(parent)
{
	fileNumber = 0;
	ui.setupUi(this);
}

ourTrackUpdater::~ourTrackUpdater()
{

}

void ourTrackUpdater::processUpdate()
{
	argList.removeFirst();
	readNextFile(fileNumber);

	return;
}

bool ourTrackUpdater::readNextFile(int num)
{
	QUrl url(argList[num]);
	
	QFileInfo fileInfo(url.path());
	QString fileName = fileInfo.fileName();
	ui.updateLabel->setText("Updating " + fileName + " ...");
	QString dir = QFileInfo(QCoreApplication::applicationFilePath()).path();
	dir.append("/" + fileName);

	if (QFile(dir).exists())
	{
		QFile(dir).remove();
	}
	pfile = new QFile(dir);
	pfile->open(QIODevice::WriteOnly);
	pmanager = new QNetworkAccessManager();
	preply = pmanager->get(QNetworkRequest(url));
	connect(preply, SIGNAL(readyRead()), this, SLOT(httpReadyRead()));
	connect(preply, SIGNAL(finished()), this, SLOT(httpFinished()));

	return true;
}

void ourTrackUpdater::httpReadyRead()
{
    if (pfile)
        pfile->write(preply->readAll());
}
 
void ourTrackUpdater::httpFinished()
{
	pfile->flush();
    pfile->close();
    preply->deleteLater();
    preply = NULL;
    delete pfile;
    pfile = NULL;

	fileNumber++;
	if (fileNumber < argList.size())
		readNextFile(fileNumber);
	else
	{
		QString dir = QFileInfo(QCoreApplication::applicationFilePath()).path();
		ourtrackProcess.start(dir +"/ourtrack.exe");
		ourtrackProcess.waitForStarted();

		exit(0);
	}
}
