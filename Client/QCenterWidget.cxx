#include "QCenterWidget.hpp"
//#include "ftitlebar.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QEasingCurve>
#include <QLabel>
#include <QTime>


QCenterWidget::QCenterWidget(QWidget *parent)
    :QFrame(parent)
{
    initData();
    initUI();
    initConnect();
}

void QCenterWidget::initData()
{
    preindex = 0;
}

void QCenterWidget::initUI()
{
    setObjectName(QString("QCenterWidget"));
    stackWidget = new QStackedWidget();

    navlayout = new QBoxLayout(QBoxLayout::TopToBottom);
    navlayout->addWidget(stackWidget);
    navlayout->setContentsMargins(0, 0 ,0 ,0);
    navlayout->setSpacing(0);

    mShowLine = new QLabel(this);
    mShowLine->setFixedHeight(2);
    mShowLine->setObjectName(QString("AntimationLine"));
    mShowLine->hide();
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mShowLine);
    mainLayout->addLayout(navlayout);
    mainLayout->setContentsMargins(0, 0 ,0 ,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
}

void QCenterWidget::swicthLayout(QBoxLayout::Direction direction)
{
    navlayout->setDirection(direction);
}



void QCenterWidget::initConnect()
{
    connect(stackWidget, SIGNAL(currentChanged(int)), this, SLOT(onChgWnd(int)));
}


void QCenterWidget::addWidget(const QString &tile, const QString &obejctName, QWidget *widget)
{
    widget->setObjectName(obejctName);
    stackWidget->addWidget(widget);
}

void QCenterWidget::switchscreen(const int index)
{
    int n = 0;
    if (index == stackWidget->currentIndex())
    {
        return;
    }
    else if(index > stackWidget->currentIndex())
    {
        n = 2;
    }
    else if (index < stackWidget->currentIndex())
    {
        n = 6;
    }
    QSize size = stackWidget->currentWidget()->size();
    stackWidget->setCurrentIndex(index);

//    QTime time;
//    time= QTime::currentTime();
//    qsrand(time.msec()+time.second()*1000);
//    int n = qrand()%9;
//    n = 0;
    switch (n) {
    case 0:
        cloudAntimation(animationTop, size);
        break;
    case 1:
        cloudAntimation(animationTopRight, size);
        break;
    case 2:
        cloudAntimation(animationRight, size);
        break;
    case 3:
        cloudAntimation(animationBottomRight, size);
        break;
    case 4:
        cloudAntimation(animationBottom, size);
        break;
    case 5:
        cloudAntimation(animationBottomLeft, size);
        break;
    case 6:
        cloudAntimation(animationLeft, size);
        break;
    case 7:
        cloudAntimation(animationTopLeft, size);
        break;
    case 8:
        cloudAntimation(animationCenter, size);
        break;
    default:
        break;
    }
    preindex = index;

}

void QCenterWidget::switchscreen(const QWidget *widget)
{
    int nIndex = -1;
    QWidget* pWidget = const_cast<QWidget*> (widget);
    if((nIndex = stackWidget->indexOf(pWidget)) >= 0)
    {
        if(nIndex == stackWidget->currentIndex())
        {
            return;
        }
        switchscreen(nIndex);
    }
}


void QCenterWidget::switchscreen()
{
    stackWidget->setCurrentIndex(currentIndex);
}

void QCenterWidget::cloudAntimation(animation_Direction direction, const QSize& size_)
{
    QLabel* circle = new QLabel(stackWidget->currentWidget());
    mShowLine->setWindowFlags(Qt::FramelessWindowHint);
   // line->move(200, 300);
    mShowLine->resize(0, 2);
    mShowLine->show();
    #if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
        circle->setPixmap(QPixmap::grabWidget(stackWidget->widget(preindex), stackWidget->widget(preindex)->geometry()));
    #else
        circle->setPixmap(stackWidget->widget(preindex)->grab());
    #endif

    //circle->setScaledContents(true);
    QSize tmpSize = stackWidget->widget(preindex)->size();
    tmpSize = tmpSize.height() > size_.height() ? tmpSize : size_;
    circle->resize(tmpSize);
    circle->show();
    QPropertyAnimation *animation = new QPropertyAnimation(circle, "geometry");

    animation->setDuration(1000);
    animation->setStartValue(circle->geometry());

    QPropertyAnimation* animation_line = new QPropertyAnimation(mShowLine, "size");
    animation_line->setDuration(1000);
    animation_line->setEasingCurve(QEasingCurve::Linear);

    switch (direction) {
    case animationTop:
        animation->setEndValue(QRect(circle->x(), circle->y() - 10, circle->width(), 0));
        break;
    case animationTopRight:
        animation->setEndValue(QRect(circle->width(), 0, 0, 0));
        break;
    case animationRight:
        mShowLine->move(0, stackWidget->y() - 2);
        animation->setEndValue(QRect(circle->width() + 3, 0, 0, circle->height()));
        animation_line->setStartValue(QSize(0, 2));
        animation_line->setEndValue(QSize(stackWidget->width(), 2));
        break;
    case animationBottomRight:
        animation->setEndValue(QRect(circle->width(), circle->height(), 0, 0));
        break;
    case animationBottom:
        animation->setEndValue(QRect(0, circle->height() + 10, circle->width(), 0));
        break;
    case animationBottomLeft:
        animation->setEndValue(QRect(0, circle->height(), 0, 0));
        break;
    case animationLeft:
        animation->setEndValue(QRect(-3, 0, 0, circle->height()));
        mShowLine->move(stackWidget->x(), stackWidget->y() - 2);
        animation_line->setStartValue(QSize(0, 2));
        animation_line->setEndValue(QSize(stackWidget->width(), 2));
        break;
    case animationTopLeft:
        animation->setEndValue(QRect(0, 0, 0, 0));
        break;
    case animationCenter:
        animation->setEndValue(QRect(circle->width()/2, circle->height()/2, 0, 0));
        break;
    default:
        break;
    }
    animation->setEasingCurve(QEasingCurve::Linear);

    QPropertyAnimation* animation_opacity = new QPropertyAnimation(circle, "windowOpacity");
    animation_opacity->setDuration(1000);
    animation_opacity->setStartValue(1);
    animation_opacity->setEndValue(0);
    animation_opacity->setEasingCurve(QEasingCurve::Linear);

    QParallelAnimationGroup *group = new QParallelAnimationGroup;

    connect(group,SIGNAL(finished()), circle, SLOT(hide()));
    connect(group,SIGNAL(finished()), circle, SLOT(deleteLater()));
    connect(group,SIGNAL(finished()), mShowLine, SLOT(hide()));
    connect(group,SIGNAL(finished()), group, SLOT(deleteLater()));
    connect(group,SIGNAL(finished()), animation, SLOT(deleteLater()));
    connect(group,SIGNAL(finished()), animation_opacity, SLOT(deleteLater()));
    connect(group,SIGNAL(finished()), animation_line, SLOT(deleteLater()));
    group->addAnimation(animation_line);

    group->addAnimation(animation);
    group->addAnimation(animation_opacity);
    group->start();
}

void QCenterWidget::onChgWnd(int nIdex)
{
    QWidget* pWidget = stackWidget->widget(nIdex);

    if(pWidget)
    {
        emit emitCurrrWnd(pWidget->windowTitle());
    }
}
