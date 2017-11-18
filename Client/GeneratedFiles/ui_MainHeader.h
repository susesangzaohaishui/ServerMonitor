/********************************************************************************
** Form generated from reading UI file 'MainHeader.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINHEADER_H
#define UI_MAINHEADER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainHeader
{
public:
    QHBoxLayout *horizontalLayout;
    QPushButton *HeaderLeft;
    QLabel *label_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QPushButton *HeaderRight;

    void setupUi(QWidget *MainHeader)
    {
        if (MainHeader->objectName().isEmpty())
            MainHeader->setObjectName(QString::fromUtf8("MainHeader"));
        MainHeader->resize(400, 38);
        MainHeader->setMinimumSize(QSize(0, 38));
        MainHeader->setMaximumSize(QSize(16777215, 42));
        MainHeader->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout = new QHBoxLayout(MainHeader);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        HeaderLeft = new QPushButton(MainHeader);
        HeaderLeft->setObjectName(QString::fromUtf8("HeaderLeft"));
        HeaderLeft->setMinimumSize(QSize(42, 42));
        HeaderLeft->setMaximumSize(QSize(42, 42));
        HeaderLeft->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"   background-color: rgb(45, 120, 82);\n"
"   background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(45, 120, 82, 255), stop:0.5 rgba(65, 190, 82, 255), stop:1 rgba(65, 118, 82, 255));\n"
"\n"
"    /*border: none;\n"
"    color: white;*/\n"
"    border-style: outset;\n"
"    border-width: 1px;\n"
"    border-radius: 5px;\n"
"    border-color: rgb(76, 148, 31);\n"
"    padding: 1px;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"    background-color: rgb(76, 148, 31);\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton:disabled{\n"
"    background-color: gray;\n"
"}\n"
"\n"
"QPushButton#checkable{\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(11, 158, 12, 255), stop:1 rgba(150, 220, 120, 255));\n"
"    border: none;\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton#checkable:hover{\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(11, 158, 12, 255), stop:0.5 rgba(150, 220, 120, 255), stop:1 rgba("
                        "11, 158, 12, 255));\n"
"    color: white;\n"
"    border-left: 5px solid rgb(255, 127, 39);\n"
"}\n"
"\n"
"QPushButton#checkable:checked{\n"
"    background-color: rgba(11, 158, 12, 255);\n"
"    color: white;\n"
"    border-left: 5px solid rgb(255, 127, 39);\n"
"}\n"
"\n"
"QPushButton#checkable:pressed{\n"
"    background-color: rgba(11, 158, 12, 255);\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton#checkable:disabled{\n"
"    background-color: gray;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/resource_image/drawer.png"), QSize(), QIcon::Normal, QIcon::Off);
        HeaderLeft->setIcon(icon);
        HeaderLeft->setFlat(true);

        horizontalLayout->addWidget(HeaderLeft);

        label_2 = new QLabel(MainHeader);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        label = new QLabel(MainHeader);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        HeaderRight = new QPushButton(MainHeader);
        HeaderRight->setObjectName(QString::fromUtf8("HeaderRight"));
        HeaderRight->setMinimumSize(QSize(42, 38));
        HeaderRight->setMaximumSize(QSize(42, 38));
        HeaderRight->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"   background-color: rgb(45, 120, 82);\n"
"   background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(24,32,46, 255), stop:0.5 rgba(24,32,46, 230), stop:1 rgba(24,32,46, 255));\n"
"\n"
"    /*border: none;\n"
"    color: white;*/\n"
"    border-style: outset;\n"
"    border-width: 1px;\n"
"    border-radius: 12px;\n"
"    border-color: rgb(75,132,146,);\n"
"    padding: 1px;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"    background-color: rgb(76,32,32);\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton:disabled{\n"
"    background-color: gray;\n"
"}\n"
"\n"
"QPushButton#checkable{\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(20,54,44, 233), stop:1 rgba(120,54,44, 255));\n"
"    border: none;\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton#checkable:hover{\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(24,32,46, 230), stop:0.5 rgba(24,32,46, 230), stop:1 rgba(24,32,46, 230));\n"
"    c"
                        "olor: white;\n"
"    border-left: 5px solid rgb(24,32,46);\n"
"}\n"
"\n"
"QPushButton#checkable:checked{\n"
"    background-color: rgba(24,32,46, 230);\n"
"    color: white;\n"
"    border-left: 5px solid rgba(24,32,46, 230);\n"
"}\n"
"\n"
"QPushButton#checkable:pressed{\n"
"    background-color: rgba(24,32,46, 230);\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton#checkable:disabled{\n"
"    background-color: gray;\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/resource_image/menu.png"), QSize(), QIcon::Normal, QIcon::Off);
        HeaderRight->setIcon(icon1);
        HeaderRight->setFlat(true);

        horizontalLayout->addWidget(HeaderRight);


        retranslateUi(MainHeader);

        QMetaObject::connectSlotsByName(MainHeader);
    } // setupUi

    void retranslateUi(QWidget *MainHeader)
    {
        MainHeader->setWindowTitle(QApplication::translate("MainHeader", "Form", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        HeaderLeft->setToolTip(QApplication::translate("MainHeader", "\345\257\274\350\210\252", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        HeaderLeft->setText(QString());
        label_2->setText(QApplication::translate("MainHeader", "Icon", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainHeader", "\347\224\265\346\212\227\346\234\215\345\212\241\347\233\221\346\216\247", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        HeaderRight->setToolTip(QApplication::translate("MainHeader", "\345\205\263\344\272\216", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        HeaderRight->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainHeader: public Ui_MainHeader {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINHEADER_H
