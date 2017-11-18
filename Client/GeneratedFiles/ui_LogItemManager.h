/********************************************************************************
** Form generated from reading UI file 'LogItemManager.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGITEMMANAGER_H
#define UI_LOGITEMMANAGER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogItemManager
{
public:

    void setupUi(QWidget *LogItemManager)
    {
        if (LogItemManager->objectName().isEmpty())
            LogItemManager->setObjectName(QString::fromUtf8("LogItemManager"));
        LogItemManager->resize(400, 300);

        retranslateUi(LogItemManager);

        QMetaObject::connectSlotsByName(LogItemManager);
    } // setupUi

    void retranslateUi(QWidget *LogItemManager)
    {
        LogItemManager->setWindowTitle(QApplication::translate("LogItemManager", "LogItemManager", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LogItemManager: public Ui_LogItemManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGITEMMANAGER_H
