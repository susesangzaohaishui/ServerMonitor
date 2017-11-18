#ifndef QLeftWidget_HPP
#define QLeftWidget_HPP

/**
  *@brief: 左窗口
  *
  *@param:
  *
  *@author: zhaoHP
  *
  *@date: 2016/10/22
  */

#include <QWidget>

#include "ui_QLeftWidget.h"
#include "QHeaderGround.hpp"

class QFlashList;

class QLeftWidget: public QWidget
{
    Q_OBJECT
public:
    QLeftWidget(QWidget* paren = NULL);

    virtual void focusOutEvent(QFocusEvent *event);

    //添加主题列表节点
    void addThreamNode(const QString& strName,
                       int serial,
                       QString NormalIcon = "",
                       QString PressIcon = "");

    //添加设置列表节点
    void addSetNode(const QString& strName,
                       int serial,
                       QString NormalIcon = "",
                       QString PressIcon = "");
    //设置标题头背景图片
    void setHeadBackPng(QString& strBackPng);

    void AnimationLeft(bool flag);

public slots:
    void showEvent(QShowEvent *_event);

    void onCloseAnima();

signals:
    void sigItem(const QString& , long);

private:
   // QFlashList*     mFlashList;
    QHeaderGround*  mHeaerGround;
    QFlashList*     mThreamList; //主题列表
    //QFlashList*     mSetList;//设置列表
    QSize       mNormalSize;
    Ui::QLeftWidget ui;
};

#endif // QLeftWidget_HPP
