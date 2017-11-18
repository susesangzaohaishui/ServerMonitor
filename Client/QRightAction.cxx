#include "QRightAction.hpp"
#include "QFlashlist.h"

#include <QPropertyAnimation>

QRightAction::QRightAction(QWidget* paren):QWidget(paren)
{

    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    setAttribute(Qt::WA_TranslucentBackground);
    //setWindowOpacity(0);
    mFlashList = new QFlashList(this);

    bool ret = connect(mFlashList, SIGNAL(sig_itemClicked(const QString&, long)), this, SLOT(onItemClicked(const QString&, long)));


    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(mFlashList);
    this->setLayout(mainLayout);
    mFlashList->addItem(QString::fromWCharArray(L"关于"),1);
    mFlashList->addItem(QString::fromWCharArray(L"退出"),2);
    mFlashList->addItem(QString::fromWCharArray(L"最小化"),3);

    mNormalSize = QSize(82, 120);

    mFlashList->setMaximumSize(mNormalSize);

    setFocusPolicy(Qt::WheelFocus);
}

void QRightAction::focusOutEvent(QFocusEvent *event)
{
   AnimationLeft(false);
   //onCloseAnima();
}

void onItemClicked()
{

}



void QRightAction::AnimationLeft(bool flag)
{

    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");

    connect(animation, SIGNAL(finished()), animation, SLOT(deleteLater()));



    QWidget* pParent = (QWidget*)parent();
    QPoint tp =  pParent->mapToGlobal(QPoint( pParent->width(), 0));



    if(flag)
    {
        this->resize(mNormalSize);
        animation->setDuration(100);
        animation->setStartValue(QRect(tp.x(), tp.y(), this->width(), this->height()));
        animation->setEndValue(QRect(tp.x() - width(), tp.y(), this->width(), this->height()));
        animation->setEasingCurve(QEasingCurve::/*InOutCubic*/Linear);
    }
    else
    {
        animation->setDuration(100);

        animation->setStartValue(QRect(tp.x() - width()  , tp.y(), this->width(), this->height()));
        animation->setEndValue(QRect(tp.x(), tp.y(), 0, this->height()));
        animation->setEasingCurve(QEasingCurve::/*InOutCubic*/Linear);
        connect(animation, SIGNAL(finished()), this, SLOT(hide()));

    }

    animation->start();
}

void QRightAction::showEvent(QShowEvent* _event)
{
   setFocus(Qt::MouseFocusReason);
    AnimationLeft(true);
    QWidget::showEvent(_event);
}

void QRightAction::onCloseAnima()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    connect(animation, SIGNAL(finished()), this, SLOT(deleteLater()));
    connect(animation, SIGNAL(finished()), this, SLOT(hide()));
    animation->setDuration(500);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
}

void QRightAction::onItemClicked(const QString&, long n)
{
    if(2 == n)
    {
        exit(0);
    }
    else if (3 == n)
    {
        sigMinSize();
    }
}


