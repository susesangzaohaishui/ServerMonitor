/********************************************************************************
** Form generated from reading UI file 'QMontinorRegisterWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QMONTINORREGISTERWIDGET_H
#define UI_QMONTINORREGISTERWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QMontinorRegisterWidget
{
public:
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QWidget *widget;

    void setupUi(QWidget *QMontinorRegisterWidget)
    {
        if (QMontinorRegisterWidget->objectName().isEmpty())
            QMontinorRegisterWidget->setObjectName(QString::fromUtf8("QMontinorRegisterWidget"));
        QMontinorRegisterWidget->resize(532, 380);
        verticalLayout_5 = new QVBoxLayout(QMontinorRegisterWidget);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        groupBox_2 = new QGroupBox(QMontinorRegisterWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        widget = new QWidget(groupBox_2);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(0, 300));

        verticalLayout_4->addWidget(widget);


        verticalLayout_5->addWidget(groupBox_2);


        retranslateUi(QMontinorRegisterWidget);

        QMetaObject::connectSlotsByName(QMontinorRegisterWidget);
    } // setupUi

    void retranslateUi(QWidget *QMontinorRegisterWidget)
    {
        QMontinorRegisterWidget->setWindowTitle(QApplication::translate("QMontinorRegisterWidget", "\347\233\221\346\216\247\350\212\202\347\202\271\346\263\250\345\206\214", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("QMontinorRegisterWidget", "\350\212\202\347\202\271\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QMontinorRegisterWidget: public Ui_QMontinorRegisterWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QMONTINORREGISTERWIDGET_H
