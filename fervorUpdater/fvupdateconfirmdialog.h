#ifndef FVUPDATECONFIRMDIALOG_H
#define FVUPDATECONFIRMDIALOG_H

#include <QtWidgets\QDialog>
#include <qfile.h>
#include <qnetworkaccessmanager.h>
#include <qnetworkreply.h>
#include <qdir.h>
#include <qcoreapplication.h>
#include <qprocess.h>

namespace Ui {
class FvUpdateConfirmDialog;
}

class FvUpdateConfirmDialog : public QDialog
{
	Q_OBJECT
	
public:
	explicit FvUpdateConfirmDialog(QWidget *parent = 0);
	~FvUpdateConfirmDialog();

	// Update the current update proposal from FvUpdater
	bool UpdateWindowWithCurrentProposedUpdate();

	void closeEvent(QCloseEvent* event);
	bool readNextFile(int num);

private:
	Ui::FvUpdateConfirmDialog* m_ui;

	QStringList urlList;
	QProcess updateProcess;
};

#endif // FVUPDATECONFIRMDIALOG_H
