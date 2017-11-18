/********************************************************************************
** Form generated from reading UI file 'ProcessLogWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROCESSLOGWIDGET_H
#define UI_PROCESSLOGWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProcessLogWidget
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QLabel *label;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_2;
    QDateTimeEdit *dateTimeEdit;
    QDateTimeEdit *dateTimeEdit_2;
    QCheckBox *checkBox;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_2;
    QWidget *widget;

    void setupUi(QWidget *ProcessLogWidget)
    {
        if (ProcessLogWidget->objectName().isEmpty())
            ProcessLogWidget->setObjectName(QString::fromUtf8("ProcessLogWidget"));
        ProcessLogWidget->resize(721, 544);
        verticalLayout_3 = new QVBoxLayout(ProcessLogWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_3 = new QLabel(ProcessLogWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        label = new QLabel(ProcessLogWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        lineEdit_2 = new QLineEdit(ProcessLogWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setMinimumSize(QSize(240, 0));

        verticalLayout_2->addWidget(lineEdit_2);

        lineEdit = new QLineEdit(ProcessLogWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMinimumSize(QSize(240, 0));

        verticalLayout_2->addWidget(lineEdit);


        horizontalLayout->addLayout(verticalLayout_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        dateTimeEdit = new QDateTimeEdit(ProcessLogWidget);
        dateTimeEdit->setObjectName(QString::fromUtf8("dateTimeEdit"));
        dateTimeEdit->setDateTime(QDateTime(QDate(2017, 1, 1), QTime(0, 0, 0)));

        horizontalLayout_2->addWidget(dateTimeEdit);

        dateTimeEdit_2 = new QDateTimeEdit(ProcessLogWidget);
        dateTimeEdit_2->setObjectName(QString::fromUtf8("dateTimeEdit_2"));
        dateTimeEdit_2->setDateTime(QDateTime(QDate(2017, 12, 31), QTime(23, 59, 59)));

        horizontalLayout_2->addWidget(dateTimeEdit_2);

        checkBox = new QCheckBox(ProcessLogWidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout_2->addWidget(checkBox);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        horizontalLayout->addLayout(horizontalLayout_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        pushButton = new QPushButton(ProcessLogWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(75, 28));
        pushButton->setMaximumSize(QSize(75, 28));

        horizontalLayout_5->addWidget(pushButton);

        pushButton_2 = new QPushButton(ProcessLogWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(75, 28));
        pushButton_2->setMaximumSize(QSize(75, 28));

        horizontalLayout_5->addWidget(pushButton_2);

        label_2 = new QLabel(ProcessLogWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(90, 0));

        horizontalLayout_5->addWidget(label_2);


        verticalLayout_3->addLayout(horizontalLayout_5);

        widget = new QWidget(ProcessLogWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(0, 400));

        verticalLayout_3->addWidget(widget);


        retranslateUi(ProcessLogWidget);

        QMetaObject::connectSlotsByName(ProcessLogWidget);
    } // setupUi

    void retranslateUi(QWidget *ProcessLogWidget)
    {
        ProcessLogWidget->setWindowTitle(QApplication::translate("ProcessLogWidget", "\346\227\245\345\277\227\345\210\206\346\236\220", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ProcessLogWidget", "IP\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ProcessLogWidget", "\350\277\233\347\250\213\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        lineEdit_2->setText(QApplication::translate("ProcessLogWidget", "127.0.0.1", 0, QApplication::UnicodeUTF8));
        lineEdit->setText(QApplication::translate("ProcessLogWidget", "Node.exe", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("ProcessLogWidget", "\346\227\266\351\227\264\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("ProcessLogWidget", "\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("ProcessLogWidget", "\346\270\205\347\220\206\346\227\245\345\277\227", 0, QApplication::UnicodeUTF8));
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ProcessLogWidget: public Ui_ProcessLogWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROCESSLOGWIDGET_H
