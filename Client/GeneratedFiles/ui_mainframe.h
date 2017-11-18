/********************************************************************************
** Form generated from reading UI file 'mainframe.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFRAME_H
#define UI_MAINFRAME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainFrame
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QWidget *header;
    QWidget *center;

    void setupUi(QWidget *MainFrame)
    {
        if (MainFrame->objectName().isEmpty())
            MainFrame->setObjectName(QString::fromUtf8("MainFrame"));
        MainFrame->resize(400, 395);
        verticalLayout_2 = new QVBoxLayout(MainFrame);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        header = new QWidget(MainFrame);
        header->setObjectName(QString::fromUtf8("header"));
        header->setMaximumSize(QSize(16777215, 167));

        verticalLayout->addWidget(header);

        center = new QWidget(MainFrame);
        center->setObjectName(QString::fromUtf8("center"));

        verticalLayout->addWidget(center);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(MainFrame);

        QMetaObject::connectSlotsByName(MainFrame);
    } // setupUi

    void retranslateUi(QWidget *MainFrame)
    {
        MainFrame->setWindowTitle(QApplication::translate("MainFrame", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainFrame: public Ui_MainFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFRAME_H
