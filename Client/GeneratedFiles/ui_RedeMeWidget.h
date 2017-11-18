/********************************************************************************
** Form generated from reading UI file 'RedeMeWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REDEMEWIDGET_H
#define UI_REDEMEWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RedeMeWidget
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;

    void setupUi(QWidget *RedeMeWidget)
    {
        if (RedeMeWidget->objectName().isEmpty())
            RedeMeWidget->setObjectName(QString::fromUtf8("RedeMeWidget"));
        RedeMeWidget->resize(440, 548);
        verticalLayout = new QVBoxLayout(RedeMeWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textEdit = new QTextEdit(RedeMeWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        verticalLayout->addWidget(textEdit);


        retranslateUi(RedeMeWidget);

        QMetaObject::connectSlotsByName(RedeMeWidget);
    } // setupUi

    void retranslateUi(QWidget *RedeMeWidget)
    {
        RedeMeWidget->setWindowTitle(QApplication::translate("RedeMeWidget", "RedeMeWidget", 0, QApplication::UnicodeUTF8));
        textEdit->setHtml(QApplication::translate("RedeMeWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:72pt; color:#ff00ff;\">\351\232\217\346\204\217\347\224\250</span></p>\n"
"<p align=\"justify\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:12pt; font-weight:600; color:#aa0000;\"><br /></p>\n"
"<p align=\"justify\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RedeMeWidget: public Ui_RedeMeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REDEMEWIDGET_H
