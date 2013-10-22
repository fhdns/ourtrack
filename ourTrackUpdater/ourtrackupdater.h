#ifndef OURTRACKUPDATER_H
#define OURTRACKUPDATER_H

#include <QtWidgets/QMainWindow>
#include "ui_ourtrackupdater.h"
#include <qurl.h>
#include <QNetworkRequest>
#include <qfile.h>
#include <qnetworkaccessmanager.h>
#include <qnetworkreply.h>
#include <qdir.h>
#include <qcoreapplication.h>
#include <qprocess.h>

class ourTrackUpdater : public QMainWindow
{
	Q_OBJECT

public:
	QStringList argList;

public:
	ourTrackUpdater(QWidget *parent = 0);
	~ourTrackUpdater();
	void processUpdate();

private:
	Ui::ourTrackUpdaterClass ui;

	int fileNumber;
	QProcess updateProcess;
	QFile * pfile;
	QNetworkAccessManager * pmanager;
	QNetworkReply * preply;
	QProcess ourtrackProcess;

private:
	bool readNextFile(int num);

private slots:
	void httpReadyRead();
	void httpFinished();
};

#endif // OURTRACKUPDATER_H
