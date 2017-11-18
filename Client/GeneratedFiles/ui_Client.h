/********************************************************************************
** Form generated from reading UI file 'Client.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ClientClass)
    {
        if (ClientClass->objectName().isEmpty())
            ClientClass->setObjectName(QString::fromUtf8("ClientClass"));
        ClientClass->resize(600, 400);
        menuBar = new QMenuBar(ClientClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        ClientClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ClientClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ClientClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ClientClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        ClientClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ClientClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ClientClass->setStatusBar(statusBar);

        retranslateUi(ClientClass);

        QMetaObject::connectSlotsByName(ClientClass);
    } // setupUi

    void retranslateUi(QMainWindow *ClientClass)
    {
        ClientClass->setWindowTitle(QApplication::translate("ClientClass", "Client", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ClientClass: public Ui_ClientClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
