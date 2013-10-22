/********************************************************************************
** Form generated from reading UI file 'fvupdatewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FVUPDATEWINDOW_H
#define UI_FVUPDATEWINDOW_H

#include <QtCore/QVariant>
#include <QtWebKitWidgets/QWebView>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FvUpdateWindow
{
public:
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout;
    QLabel *newVersionIsAvailableLabel;
    QLabel *wouldYouLikeToDownloadLabel;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_7;
    QWebView *releaseNotesWebView;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *skipThisVersionButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *remindMeLaterButton;
    QPushButton *installUpdateButton;

    void setupUi(QWidget *FvUpdateWindow)
    {
        if (FvUpdateWindow->objectName().isEmpty())
            FvUpdateWindow->setObjectName(QStringLiteral("FvUpdateWindow"));
        FvUpdateWindow->resize(640, 480);
        horizontalLayout_6 = new QHBoxLayout(FvUpdateWindow);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        newVersionIsAvailableLabel = new QLabel(FvUpdateWindow);
        newVersionIsAvailableLabel->setObjectName(QStringLiteral("newVersionIsAvailableLabel"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        newVersionIsAvailableLabel->setFont(font);

        verticalLayout->addWidget(newVersionIsAvailableLabel);

        wouldYouLikeToDownloadLabel = new QLabel(FvUpdateWindow);
        wouldYouLikeToDownloadLabel->setObjectName(QStringLiteral("wouldYouLikeToDownloadLabel"));

        verticalLayout->addWidget(wouldYouLikeToDownloadLabel);

        groupBox = new QGroupBox(FvUpdateWindow);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setFont(font);
        horizontalLayout_7 = new QHBoxLayout(groupBox);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        releaseNotesWebView = new QWebView(groupBox);
        releaseNotesWebView->setObjectName(QStringLiteral("releaseNotesWebView"));
        releaseNotesWebView->setMinimumSize(QSize(160, 80));
        releaseNotesWebView->setUrl(QUrl(QStringLiteral("about:blank")));

        horizontalLayout_7->addWidget(releaseNotesWebView);


        verticalLayout->addWidget(groupBox);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        skipThisVersionButton = new QPushButton(FvUpdateWindow);
        skipThisVersionButton->setObjectName(QStringLiteral("skipThisVersionButton"));

        horizontalLayout_3->addWidget(skipThisVersionButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        remindMeLaterButton = new QPushButton(FvUpdateWindow);
        remindMeLaterButton->setObjectName(QStringLiteral("remindMeLaterButton"));

        horizontalLayout_3->addWidget(remindMeLaterButton);

        installUpdateButton = new QPushButton(FvUpdateWindow);
        installUpdateButton->setObjectName(QStringLiteral("installUpdateButton"));
        installUpdateButton->setAutoDefault(true);
        installUpdateButton->setDefault(true);

        horizontalLayout_3->addWidget(installUpdateButton);


        verticalLayout->addLayout(horizontalLayout_3);


        horizontalLayout_6->addLayout(verticalLayout);


        retranslateUi(FvUpdateWindow);

        QMetaObject::connectSlotsByName(FvUpdateWindow);
    } // setupUi

    void retranslateUi(QWidget *FvUpdateWindow)
    {
        FvUpdateWindow->setWindowTitle(QApplication::translate("FvUpdateWindow", "Software Update", 0));
        newVersionIsAvailableLabel->setText(QApplication::translate("FvUpdateWindow", "A new version of %1 is available!", 0));
        wouldYouLikeToDownloadLabel->setText(QApplication::translate("FvUpdateWindow", "%1 %2 is now available - you have %3. Would you like to download it now?", 0));
        groupBox->setTitle(QApplication::translate("FvUpdateWindow", "Release Notes:", 0));
        skipThisVersionButton->setText(QApplication::translate("FvUpdateWindow", "Skip This Version", 0));
        remindMeLaterButton->setText(QApplication::translate("FvUpdateWindow", "Remind Me Later", 0));
        installUpdateButton->setText(QApplication::translate("FvUpdateWindow", "Install Update", 0));
    } // retranslateUi

};

namespace Ui {
    class FvUpdateWindow: public Ui_FvUpdateWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FVUPDATEWINDOW_H
