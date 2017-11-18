#include "MainFrame.hpp"
#include "MainHeader.hpp"
#include "QLeftWidget.hpp"
#include "QCenterWidget.hpp"
#include "QRightAction.hpp"
#include "QSliderButton.h"
#include "QDebugConsole.hpp"

//#include "QBaseCamera.hpp"

#include <QResizeEvent>


enum Direction
{
    MainFrame_up = 0,
    MainFrame_down,
    MainFrame_left,
    MainFrame_right,
    MainFrame_lefttop,
    MainFrame_leftbottom,
    MainFrame_rightbottom,
    MainFrame_righttop,
    MainFrame_none
};

MainFrame::MainFrame(QWidget *parent) :
    QWidget(parent),
    mBDrag(false)

{

    ui.setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    //主窗口标题栏
    mHeader = new MainHeader(this);
    mHeader->setObjectName("MainHeaderObj");
    QVBoxLayout* headerLayout = new QVBoxLayout(this);
    headerLayout->setObjectName("HeaderLayoutFrame");
    headerLayout->addWidget(mHeader);
    headerLayout->setContentsMargins(0, 0, 0, 0);
    headerLayout->setSpacing(0);
    ui.header->setLayout(headerLayout);

    //界面中心
    mCenter = new QCenterWidget(this);
    QVBoxLayout* centerLayout = new QVBoxLayout(this);
    centerLayout->setContentsMargins(0, 0, 0, 0);
    centerLayout->setSpacing(0);
    centerLayout->setObjectName("centerLayoutFrame");
    centerLayout->addWidget(mCenter);
    ui.center->setLayout(centerLayout);

    //左列表
    //@@mLeftList = new QLeftWidget(this);
    mRightAct = new QRightAction(this);

    connect(mHeader, SIGNAL(sigMove(QPoint&)), this,SLOT(onMove(QPoint&)));
    connect(mHeader, SIGNAL(sigShowLight()), this, SLOT(onShowLight()));
    connect(mHeader, SIGNAL(sigShowRight()), this, SLOT(onShowRight()));
    connect(mCenter, SIGNAL(emitCurrrWnd(const QString& )), this, SLOT(onSetWindowTle(const QString&)));
    //@@connect(mLeftList, SIGNAL(sigItem(const QString&, long)), this, SLOT(onItemClicked(const QString&, long)));
   bool retb = connect(mRightAct, SIGNAL(sigMinSize()), this, SLOT(showMinimized()));


    this->resize(870, 540);

    testWidget();

    setWindowIcon(QIcon(":image/spincursor.png"));

    setWindowTitle(QString::fromWCharArray(L"电抗服务监控"));
}

//测试代码
void MainFrame::testWidget()
{
}

MainFrame::~MainFrame()
{
    delete mHeader;
    delete mCenter;
    //@@delete mLeftList;
    QDebugConsole::release();
}

void MainFrame::resizeEvent(QResizeEvent *e)
{
    mHeader->resize(e->size().width(), mHeader->height());
    //qDebug()<<rect();
}

void MainFrame::mouseMoveEvent(QMouseEvent *e)
{

    if(isMaximized() &&
            (e->y() < mHeader->height()) &&
            (e->x() < mHeader->width() - 20)&&
            (e->x() < mHeader->width() + 20))
    {
        showNormal();
        mBDrag = false;
        e->ignore();
    }
    else
    {
        if(e->y() < mHeader->height() && e->x() > mHeader->width() - 20)
        {
            e->ignore();
        }
        else{
            if(mBDrag)
            {

                move(e->globalPos() - mTgtPnt);
                e->accept();
            }

        }
    }
}

void MainFrame::mousePressEvent(QMouseEvent *e)
{
    if(e->button() & Qt::LeftButton)
    {
        mTgtPnt = e->globalPos() - frameGeometry().topLeft();

        if(e->y() < mHeader->height() &&
                (e->x() < mHeader->width() - 20)&&
                (e->x() < mHeader->width() + 20))
        {
            mBDrag = true;
        }
        else
        {
            mBDrag = false;
        }
    }
    e->accept();

}

void MainFrame::mouseDoubleClickEvent(QMouseEvent *e)
{
    if((e->y() < mHeader->height()) &&
            (e->x() < mHeader->width() - 20)&&
            (e->x() < mHeader->width() + 20))
    {
        onMaxMinized();
        e->accept();
    }else{
        e->ignore();
    }
}

void MainFrame::addCenterWidget(const QString& title,
                                const QString& ojbName,
                                int serial,
                                 enumCenterType type,
                                QWidget *widget)
{

    //如果有对应的编号则不添加窗口
    WidgetType::const_iterator i = mWidgetType.find(serial);
    if(i != mWidgetType.end())
    {
        return;
    }

    widget->setWindowTitle(title);

    //设置窗口类型与搜索信息
    ExtenType SeriType;
    SeriType.first = type;
    SeriType.second = widget;
    mWidgetType.insert(serial, SeriType);

    //@@mLeftList->addThreamNode(title, serial);

    if(type == eWidgetEmbed)
    {
        mCenter->addWidget(title, ojbName, widget);
    }
}

void MainFrame::addSetWidget(const QString &title,
                             const QString &ojbName,
                             int serial,
                             enumCenterType type,
                             QWidget *widget)
{
    WidgetType::const_iterator i = mWidgetType.find(serial);
    if(i != mWidgetType.end())
    {
        return;
    }

    widget->setWindowTitle(title);

    //设置窗口类型与搜索信息
    ExtenType SeriType;
    SeriType.first = type;
    SeriType.second = widget;
    mWidgetType.insert(serial, SeriType);

    //@@mLeftList->addSetNode(title, serial);

    if(type == eWidgetEmbed)
    {
        mCenter->addWidget(title, ojbName, widget);
    }
}


void MainFrame::mouseReleaseEvent(QMouseEvent *e)
{
    mBDrag = false;
    e->accept();
}

void MainFrame::onMaxMinized()
{
    if(this->isMaximized())
    {
        this->showNormal();
    }
    else
    {
        this->showMaximized();
    }
}

void MainFrame::onMove(QPoint& pnt)
{
    move(pnt);
}

void MainFrame::onShowLight()
{
    //@@mLeftList->show();
    //@@mLeftList->setFocus(Qt::MouseFocusReason);
}
void MainFrame::onShowRight()
{
    mRightAct->show();
}

void MainFrame::onSetWindowTle(const QString &tille)
{
    mHeader->setHeaderText(tille);
}

void MainFrame::onItemClicked(const QString& , long serial)
{

    //@@mLeftList->AnimationLeft(false);
    WidgetType::const_iterator i = mWidgetType.find(serial);
    if(i != mWidgetType.end())
    {
        switch(i->first)
        {
            case  eWidgetPop:
            {
                if(i->second->isHidden())
                {
                    i->second->show();
                }
                else
                {
                    i->second->hide();
                }
            }
            break;
            case  eWidgetEmbed:
            {

                mCenter->switchscreen(i->second);
            }
            break;

        }
    }


}

//MainFrame::region(const QPoint& cusourGlobalPnt)
//{
//    //鑾峰彇绐椾綋鍦ㄥ睆骞曚笂鐨勪綅缃尯鍩?
//    QPoint tl = mapToGlobal(rect().topLeft());
//    QPoint br = mapToGlobal(rect().bottomRight());
//    QPoint br = mapToGlobal(rect().bottomRight());
//
//}
