/********************************************************************************
** Form generated from reading UI file 'ourtrack.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OURTRACK_H
#define UI_OURTRACK_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ourtrackClass
{
public:
    QAction *menuFind;
    QAction *menuSettings;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_SearchGroup;
    QLineEdit *EditFind;
    QPushButton *ButtonFind;
    QTableWidget *TableResult;
    QMenuBar *menuBar;
    QMenu *menuMain;
    QMenu *menuOptions;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *ourtrackClass)
    {
        if (ourtrackClass->objectName().isEmpty())
            ourtrackClass->setObjectName(QStringLiteral("ourtrackClass"));
        ourtrackClass->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ourtrackClass->sizePolicy().hasHeightForWidth());
        ourtrackClass->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QStringLiteral(":/ourtrack/explorer.png"), QSize(), QIcon::Normal, QIcon::Off);
        ourtrackClass->setWindowIcon(icon);
        ourtrackClass->setLayoutDirection(Qt::LeftToRight);
        ourtrackClass->setAutoFillBackground(true);
        ourtrackClass->setLocale(QLocale(QLocale::Russian, QLocale::Russia));
        menuFind = new QAction(ourtrackClass);
        menuFind->setObjectName(QStringLiteral("menuFind"));
        menuSettings = new QAction(ourtrackClass);
        menuSettings->setObjectName(QStringLiteral("menuSettings"));
        centralWidget = new QWidget(ourtrackClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setAutoFillBackground(false);
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_SearchGroup = new QHBoxLayout();
        horizontalLayout_SearchGroup->setSpacing(6);
        horizontalLayout_SearchGroup->setObjectName(QStringLiteral("horizontalLayout_SearchGroup"));
        EditFind = new QLineEdit(centralWidget);
        EditFind->setObjectName(QStringLiteral("EditFind"));

        horizontalLayout_SearchGroup->addWidget(EditFind);

        ButtonFind = new QPushButton(centralWidget);
        ButtonFind->setObjectName(QStringLiteral("ButtonFind"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ButtonFind->sizePolicy().hasHeightForWidth());
        ButtonFind->setSizePolicy(sizePolicy1);
        ButtonFind->setMinimumSize(QSize(125, 23));
        ButtonFind->setMaximumSize(QSize(125, 23));
        ButtonFind->setLayoutDirection(Qt::LeftToRight);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/ourtrack/camera.png"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonFind->setIcon(icon1);
        ButtonFind->setAutoDefault(true);
        ButtonFind->setDefault(true);

        horizontalLayout_SearchGroup->addWidget(ButtonFind);


        verticalLayout->addLayout(horizontalLayout_SearchGroup);

        TableResult = new QTableWidget(centralWidget);
        TableResult->setObjectName(QStringLiteral("TableResult"));
        TableResult->setShowGrid(true);
        TableResult->setSortingEnabled(true);
        TableResult->setRowCount(0);
        TableResult->setColumnCount(0);
        TableResult->verticalHeader()->setDefaultSectionSize(20);

        verticalLayout->addWidget(TableResult);

        ourtrackClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ourtrackClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        menuMain = new QMenu(menuBar);
        menuMain->setObjectName(QStringLiteral("menuMain"));
        menuOptions = new QMenu(menuBar);
        menuOptions->setObjectName(QStringLiteral("menuOptions"));
        ourtrackClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ourtrackClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ourtrackClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ourtrackClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ourtrackClass->setStatusBar(statusBar);
        toolBar = new QToolBar(ourtrackClass);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        ourtrackClass->addToolBar(Qt::TopToolBarArea, toolBar);

        menuBar->addAction(menuMain->menuAction());
        menuBar->addAction(menuOptions->menuAction());
        menuMain->addAction(menuFind);
        menuOptions->addAction(menuSettings);

        retranslateUi(ourtrackClass);
        QObject::connect(EditFind, SIGNAL(returnPressed()), ButtonFind, SLOT(click()));

        QMetaObject::connectSlotsByName(ourtrackClass);
    } // setupUi

    void retranslateUi(QMainWindow *ourtrackClass)
    {
        ourtrackClass->setWindowTitle(QApplication::translate("ourtrackClass", "OurTrack", 0));
        menuFind->setText(QApplication::translate("ourtrackClass", "\320\235\320\260\320\271\321\202\320\270", 0));
        menuSettings->setText(QApplication::translate("ourtrackClass", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", 0));
        ButtonFind->setText(QApplication::translate("ourtrackClass", "Find", 0));
        menuMain->setTitle(QApplication::translate("ourtrackClass", "\320\223\320\273\320\260\320\262\320\275\320\260\321\217", 0));
        menuOptions->setTitle(QApplication::translate("ourtrackClass", "\320\236\320\277\321\206\320\270\320\270", 0));
        toolBar->setWindowTitle(QApplication::translate("ourtrackClass", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class ourtrackClass: public Ui_ourtrackClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OURTRACK_H
