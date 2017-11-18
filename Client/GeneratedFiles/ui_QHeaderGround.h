/********************************************************************************
** Form generated from reading UI file 'QHeaderGround.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QHEADERGROUND_H
#define UI_QHEADERGROUND_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QHeaderGround
{
public:
    QVBoxLayout *verticalLayout_2;

    void setupUi(QWidget *QHeaderGround)
    {
        if (QHeaderGround->objectName().isEmpty())
            QHeaderGround->setObjectName(QString::fromUtf8("QHeaderGround"));
        QHeaderGround->resize(742, 788);
        QHeaderGround->setStyleSheet(QString::fromUtf8("background-image: url(:/image/resource_image/Circle.png);\n"
"background-color: rgb(0, 0, 0);"));
        verticalLayout_2 = new QVBoxLayout(QHeaderGround);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);

        retranslateUi(QHeaderGround);

        QMetaObject::connectSlotsByName(QHeaderGround);
    } // setupUi

    void retranslateUi(QWidget *QHeaderGround)
    {
        Q_UNUSED(QHeaderGround);
    } // retranslateUi

};

namespace Ui {
    class QHeaderGround: public Ui_QHeaderGround {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QHEADERGROUND_H
