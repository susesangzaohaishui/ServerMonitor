#include "QLeftWidget.hpp"
#include "QFlashlist.h"

#include <QDebug>
#include <QBrush>
#include <QPalette>
#include <QPropertyAnimation>

QLeftWidget::QLeftWidget(QWidget* paren):QWidget(paren)
{


    ui.setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    mNormalSize = this->size();
    setFocusPolicy(Qt::WheelFocus);

    mHeaerGround = new QHeaderGround(this);
    QHBoxLayout* HderLayout = new QHBoxLayout(mHeaerGround);
    HderLayout->addWidget(mHeaerGround);
    ui.ThreamHeader->setLayout(HderLayout);
    HderLayout->setContentsMargins(0, 0, 0, 0);
    HderLayout->setSpacing(0);

    //主题列表
    mThreamList = new QFlashList(this);

    QHBoxLayout* ThearmListLayout = new QHBoxLayout(mHeaerGround);
    ThearmListLayout->addWidget(mThreamList);
    ui.ThreamWidget->setLayout(ThearmListLayout);
    ThearmListLayout->setContentsMargins(0, 0, 0, 0);
    ThearmListLayout->setSpacing(0);

    //设置列表
    //mSetList = new QFlashList(this);

    //设置用户名称
    mHeaerGround->setUserName(QString::fromWCharArray(L"电抗服务监控"));

  //  QHBoxLayout* mSetListLayout = new QHBoxLayout(mHeaerGround);
  //  mSetListLayout->addWidget(mSetList);
    //ui.setList->setLayout(mSetListLayout);
    //mSetListLayout->setContentsMargins(0, 0, 0, 0);
    //mSetListLayout->setSpacing(0);

    bool ret = connect(mThreamList, SIGNAL(sig_itemClicked(const QString& , long )),this, SIGNAL(sigItem(const QString& , long)));
   // ret = connect(mSetList, SIGNAL(sig_itemClicked(const QString& , long )),this, SIGNAL(sigItem(const QString& , long)));

//	ui.line->hide();
}

void QLeftWidget::focusOutEvent(QFocusEvent *event)
{
    //AnimationLeft(false);
   // onCloseAnima();
}

void QLeftWidget::addThreamNode(const QString &strName, int serial, QString NormalIcon, QString PressIcon)
{
    mThreamList->addItem(strName, serial);
}

void QLeftWidget::addSetNode(const QString &strName, int serial, QString NormalIcon, QString PressIcon)
{
   // mSetList->addItem(strName, serial);
}

void QLeftWidget::setHeadBackPng(QString &strBackPng)
{
    mHeaerGround->setHeadBackPng(strBackPng);
}



void QLeftWidget::AnimationLeft(bool flag)
{

    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");

    connect(animation, SIGNAL(finished()), animation, SLOT(deleteLater()));

    QWidget* pParent = (QWidget*)parent();
    QPoint tp =  pParent->mapToGlobal(QPoint( 0, 0));

    if(flag)
    {
        this->resize(mNormalSize);
        animation->setDuration(230);
        animation->setStartValue(QRect(tp.x(), tp.y(), 0, 0));
        animation->setEndValue(QRect(tp.x(), tp.y(), this->width(), this->height()));
        animation->setEasingCurve(QEasingCurve::/*InOutCubic*/Linear);
    }
    else
    {
        QCoreApplication::processEvents();
        qDebug()<<ui.ThreamHeader->rect();

        animation->setDuration(220);
       // mNormalSize = this->size();
        animation->setStartValue(QRect(tp.x(), tp.y(), this->width(), this->height()));
        animation->setEndValue(QRect(tp.x() , tp.y(), 0, 0));
        animation->setEasingCurve(QEasingCurve::/*InOutCubic*/Linear);
        connect(animation, SIGNAL(finished()), this, SLOT(hide()));

    }

    animation->start();
}

void QLeftWidget::showEvent(QShowEvent* _event)
{
   // setFocus(Qt::MouseFocusReason);
    AnimationLeft(true);
    QWidget::showEvent(_event);
}

void QLeftWidget::onCloseAnima()
{

    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
   // connect(animation, SIGNAL(finished()), this, SLOT(deleteLater()));
    connect(animation, SIGNAL(finished()), this, SLOT(hide()));
    animation->setDuration(500);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
}


