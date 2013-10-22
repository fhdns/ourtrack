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
#include <QtWebKitWidgets/QWebView>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ourtrackClass
{
public:
    QAction *menuFind;
    QAction *menuSettings;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *EditFind;
    QPushButton *ButtonFind;
    QHBoxLayout *horizontalLayout;
    QTableWidget *TableResult;
    QWebView *DescriptionBrowser;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ourtrackClass)
    {
        if (ourtrackClass->objectName().isEmpty())
            ourtrackClass->setObjectName(QStringLiteral("ourtrackClass"));
        ourtrackClass->resize(1000, 449);
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
        ourtrackClass->setLocale(QLocale(QLocale::Russian, QLocale::RussianFederation));
        menuFind = new QAction(ourtrackClass);
        menuFind->setObjectName(QStringLiteral("menuFind"));
        menuSettings = new QAction(ourtrackClass);
        menuSettings->setObjectName(QStringLiteral("menuSettings"));
        centralWidget = new QWidget(ourtrackClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setAutoFillBackground(false);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        EditFind = new QLineEdit(centralWidget);
        EditFind->setObjectName(QStringLiteral("EditFind"));

        horizontalLayout_2->addWidget(EditFind);

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

        horizontalLayout_2->addWidget(ButtonFind);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        TableResult = new QTableWidget(centralWidget);
        TableResult->setObjectName(QStringLiteral("TableResult"));
        TableResult->setMinimumSize(QSize(300, 0));
        TableResult->setBaseSize(QSize(200, 0));
        TableResult->setSelectionMode(QAbstractItemView::SingleSelection);
        TableResult->setSelectionBehavior(QAbstractItemView::SelectRows);
        TableResult->setShowGrid(true);
        TableResult->setGridStyle(Qt::SolidLine);
        TableResult->setSortingEnabled(true);
        TableResult->setRowCount(0);
        TableResult->setColumnCount(0);
        TableResult->verticalHeader()->setDefaultSectionSize(20);

        horizontalLayout->addWidget(TableResult);

        DescriptionBrowser = new QWebView(centralWidget);
        DescriptionBrowser->setObjectName(QStringLiteral("DescriptionBrowser"));
        DescriptionBrowser->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(DescriptionBrowser->sizePolicy().hasHeightForWidth());
        DescriptionBrowser->setSizePolicy(sizePolicy2);
        DescriptionBrowser->setMinimumSize(QSize(200, 0));
        DescriptionBrowser->setMaximumSize(QSize(500, 16777215));
        DescriptionBrowser->setBaseSize(QSize(0, 0));
        DescriptionBrowser->setUrl(QUrl(QStringLiteral("about:blank")));

        horizontalLayout->addWidget(DescriptionBrowser);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        ourtrackClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ourtrackClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ourtrackClass->setStatusBar(statusBar);

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
    } // retranslateUi

};

namespace Ui {
    class ourtrackClass: public Ui_ourtrackClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OURTRACK_H
