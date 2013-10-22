/********************************************************************************
** Form generated from reading UI file 'ourtrackupdater.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OURTRACKUPDATER_H
#define UI_OURTRACKUPDATER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ourTrackUpdaterClass
{
public:
    QWidget *centralWidget;
    QLabel *updateLabel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ourTrackUpdaterClass)
    {
        if (ourTrackUpdaterClass->objectName().isEmpty())
            ourTrackUpdaterClass->setObjectName(QStringLiteral("ourTrackUpdaterClass"));
        ourTrackUpdaterClass->resize(283, 101);
        ourTrackUpdaterClass->setContextMenuPolicy(Qt::NoContextMenu);
        ourTrackUpdaterClass->setToolButtonStyle(Qt::ToolButtonIconOnly);
        ourTrackUpdaterClass->setTabShape(QTabWidget::Rounded);
        ourTrackUpdaterClass->setDockOptions(QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        centralWidget = new QWidget(ourTrackUpdaterClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        updateLabel = new QLabel(centralWidget);
        updateLabel->setObjectName(QStringLiteral("updateLabel"));
        updateLabel->setGeometry(QRect(20, 10, 341, 16));
        QFont font;
        font.setPointSize(10);
        updateLabel->setFont(font);
        updateLabel->setFrameShape(QFrame::NoFrame);
        ourTrackUpdaterClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ourTrackUpdaterClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 283, 21));
        ourTrackUpdaterClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ourTrackUpdaterClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ourTrackUpdaterClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ourTrackUpdaterClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ourTrackUpdaterClass->setStatusBar(statusBar);

        retranslateUi(ourTrackUpdaterClass);

        QMetaObject::connectSlotsByName(ourTrackUpdaterClass);
    } // setupUi

    void retranslateUi(QMainWindow *ourTrackUpdaterClass)
    {
        ourTrackUpdaterClass->setWindowTitle(QApplication::translate("ourTrackUpdaterClass", "ourTrackUpdater", 0));
        updateLabel->setText(QApplication::translate("ourTrackUpdaterClass", "Updating ", 0));
    } // retranslateUi

};

namespace Ui {
    class ourTrackUpdaterClass: public Ui_ourTrackUpdaterClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OURTRACKUPDATER_H
