/********************************************************************************
** Form generated from reading UI file 'QLeftWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QLEFTWIDGET_H
#define UI_QLEFTWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QLeftWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QWidget *ThreamHeader;
    QWidget *ThreamWidget;

    void setupUi(QWidget *QLeftWidget)
    {
        if (QLeftWidget->objectName().isEmpty())
            QLeftWidget->setObjectName(QString::fromUtf8("QLeftWidget"));
        QLeftWidget->resize(252, 194);
        verticalLayout_2 = new QVBoxLayout(QLeftWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        ThreamHeader = new QWidget(QLeftWidget);
        ThreamHeader->setObjectName(QString::fromUtf8("ThreamHeader"));
        ThreamHeader->setMinimumSize(QSize(189, 0));
        ThreamHeader->setMaximumSize(QSize(16777215, 110));
        ThreamHeader->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(ThreamHeader);

        ThreamWidget = new QWidget(QLeftWidget);
        ThreamWidget->setObjectName(QString::fromUtf8("ThreamWidget"));
        ThreamWidget->setMaximumSize(QSize(16777215, 80));

        verticalLayout->addWidget(ThreamWidget);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(QLeftWidget);

        QMetaObject::connectSlotsByName(QLeftWidget);
    } // setupUi

    void retranslateUi(QWidget *QLeftWidget)
    {
        Q_UNUSED(QLeftWidget);
    } // retranslateUi

};

namespace Ui {
    class QLeftWidget: public Ui_QLeftWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QLEFTWIDGET_H
