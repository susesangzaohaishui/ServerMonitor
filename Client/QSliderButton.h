
/**
  *@brief: 具有动画功能的tab
  *
  *@param:
  *
  *@author: zhaoHP
  *
  *@date: 2016/10/22
  */

#ifndef MYSLIDEBUTTON_H
#define MYSLIDEBUTTON_H

#define PYSB_EXTRA_SPACE 15
#define PYSB_RECT_RADIUS 8
#define PYSB_HEIGHT 42

//#define PYSB_BG_START_COLOR QColor(45, 120, 82)
//#define PYSB_BG_END_COLOR   QColor(45, 120, 82)

#define PYSB_BG_START_COLOR QColor(24, 32, 46)
#define PYSB_BG_END_COLOR   QColor(24, 32, 46)

#define PYSB_BAR_SKIN1

#ifdef PYSB_BAR_SKIN1
#define PYSB_BAR_START_COLOR QColor(46,132,243)
#define PYSB_BAR_END_COLOR QColor(39,110,203)
#endif

#ifdef PYSB_BAR_SKIN2
#define PYSB_BAR_START_COLOR QColor(255,177,42)
#define PYSB_BAR_END_COLOR QColor(225,156,37)
#endif

#ifdef PYSB_BAR_SKIN3
#define PYSB_BAR_START_COLOR QColor(148,255,82)
#define PYSB_BAR_END_COLOR QColor(133,229,73)
#endif

#define PYSB_TEXT_COLOR Qt::white

#define PYSB_BAR_WIDTH_INCREMENT 2
#define PYSB_BAR_SLIDE_INCREMENT 3

#define PYSB_SLIDE_TIMER_INTERVAL 20
#define PYSB_SHRINK_TIMER_INTERVAL 20//30

#define FIREUP_SHRINK_TIMER     if(m_BarRect.width() > m_TargetRect.width()) \
                                { \
                                    m_bShrink = true; \
                                    m_shrinkTimer->start(); \
                                }else{ \
                                    m_bShrink = false; \
                                    m_shrinkTimer->start(); \
                                }



#ifdef DEBUG_VAR
#undef DEBUG_VAR
#endif
#define DEBUG_VAR(VAR) qDebug() << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << #VAR << ":" <<  VAR;

#include <QDebug>
#include <QWidget>
#include <QtGui>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QMouseEvent>

typedef QPair<double, QColor> QBgColor;
typedef QVector<QBgColor> QBgColors;

class QSliderButton : public QWidget
{
    Q_OBJECT
public:
    explicit QSliderButton(QWidget *parent = 0);
    ~QSliderButton();

public:
	//传入标题，和窗口信息
    bool addItem(const QString& str, QWidget* widget);

    void ChangePage(QWidget* );//切换页面

    void setBackColors(QBgColors& colors)
    {
        mBackColors = colors;
    }
    void setBtnColors(QBgColors& colors)
    {
        mBtnColors = colors;
    }

protected:
    virtual void mousePressEvent(QMouseEvent *);
    virtual void paintEvent(QPaintEvent *);
    QSize sizeHint() const
    {
        return QSize(300,50);
    }

private:
    void drawBg(QPainter* painter);
    void drawBar(QPainter* painter);
    void drawText(QPainter* painter);

private:
    void calcGeo();
    unsigned int GetSlideIncrement();
    void SetSlideIncrement(unsigned int nInc);
    unsigned int GetSlideIncrementInit(unsigned int nDistance);


private:

	typedef struct itemInfo
	{
		QWidget* widget;
		QRectF	 rect;
	};

    QVector< QPair<QString,itemInfo> > m_StrRectPairVec;
    QRectF  m_BarRect;
    QRectF  m_TargetRect;

    qreal   m_totalLength;

    bool m_bForward;
    bool m_bShrink;
    bool m_bVirgin;

    QTimer* m_slideTimer;
    QTimer* m_shrinkTimer;

    unsigned int m_nInc;

    QBgColors   mBtnColors;//按钮颜色列表
    QBgColors   mBackColors;//背景颜色列表


private slots:
    void DoSliding();
    void DoShrinking();

signals:
    void sig_itemClicked( QWidget* str);

};

#endif // MYSLIDEBUTTON_H
