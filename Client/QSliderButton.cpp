#include "QSliderButton.h"

QSliderButton::QSliderButton(QWidget *parent) :
    QWidget(parent)
{

    mBtnColors.push_back(QBgColor(0.0, QColor(220,220,220, 0)));
    mBtnColors.push_back(QBgColor(0.92, QColor(220,220,220, 90)));
    mBtnColors.push_back(QBgColor(0.95, QColor(255,255,255)));
    mBtnColors.push_back(QBgColor(1, QColor(255,255,255)));

    mBackColors.push_back(QBgColor(0.0,PYSB_BG_START_COLOR));
    mBackColors.push_back(QBgColor(1.0,PYSB_BG_END_COLOR));

    m_bForward = true;
    m_bShrink = false;
    m_bVirgin = true;

    m_slideTimer = new QTimer(this);
    m_slideTimer->setInterval(PYSB_SLIDE_TIMER_INTERVAL);
    connect(m_slideTimer,SIGNAL(timeout()),this,SLOT(DoSliding()));

    m_shrinkTimer = new QTimer(this);
    m_shrinkTimer->setInterval(PYSB_SHRINK_TIMER_INTERVAL);
    connect(m_shrinkTimer,SIGNAL(timeout()),this,SLOT(DoShrinking()));

    setFixedHeight(PYSB_HEIGHT);//设置固定高度
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);

}

QSliderButton::~QSliderButton()
{
	QVector< QPair<QString,itemInfo> >::Iterator it = m_StrRectPairVec.begin();
	for ( ; it != m_StrRectPairVec.end(); ++it)
	{
		delete it->second.widget;
	}
}

void QSliderButton::calcGeo()
{
    //计算文字在界面的坐标位置
    int ItemCnt = m_StrRectPairVec.count();
    qreal initX = 0;
    qreal textWidth = 0;
    QString strText;
    for(int ItemIndex = 0;ItemIndex < ItemCnt ;ItemIndex++)
    {
        //计算文字的长度与宽度
        strText = m_StrRectPairVec.at(ItemIndex).first;
        textWidth  = fontMetrics().width(strText);
        QPointF topLeft(initX,0);
        QPointF bottomRight(initX + textWidth + 2 * PYSB_EXTRA_SPACE,height());
        QRectF textRect(topLeft,bottomRight);

        m_StrRectPairVec[ItemIndex].second.rect = textRect;
        if(m_bVirgin)
        {
            m_BarRect = textRect;
            m_bVirgin = false;
        }
        //移动X轴
        initX +=textWidth + 2 * PYSB_EXTRA_SPACE;
    }

    //设置固定宽度
    //setFixedWidth(initX);
}

void QSliderButton::mousePressEvent(QMouseEvent *e)
{


    if(e->button() & Qt::LeftButton)
    {
        int ItemCnt = m_StrRectPairVec.count();
        QString strText;
        for(int ItemIndex = 0;ItemIndex < ItemCnt ; ItemIndex++)
        {
            if(m_StrRectPairVec.at(ItemIndex).second.rect.contains(e->pos()))
            {
                QString tmpstrText = m_StrRectPairVec.at(ItemIndex).first;
                strText = tmpstrText;
                DEBUG_VAR(strText);

                emit sig_itemClicked(m_StrRectPairVec.at(ItemIndex).second.widget);

                m_TargetRect = m_StrRectPairVec.at(ItemIndex).second.rect;

                if(m_TargetRect.width() > m_BarRect.width())
                {
                    m_bShrink = false;
                }else{
                    m_bShrink = true;
                }

                if(m_TargetRect.topLeft().x() > m_BarRect.topLeft().x() )
                {
                    m_bForward = true;
                }else{
                    m_bForward = false;
                }

                int distance = m_TargetRect.topLeft().x() - m_BarRect.topLeft().x();
                if(distance < 0)
                    distance = 0 - distance;

                QString tmp = QString("%1").arg(distance);
                DEBUG_VAR(tmp);


                SetSlideIncrement(GetSlideIncrementInit((unsigned int)distance)/*PYSB_BAR_SLIDE_INCREMENT_INIT*/);
                m_slideTimer->start();
                FIREUP_SHRINK_TIMER;
            }
        }
    }
}

void QSliderButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing);
    drawBg(&painter);//绘制背景
    drawBar(&painter);
    drawText(&painter);
}

void QSliderButton::drawBar(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    QLinearGradient BarGradient(m_BarRect.topLeft(),m_BarRect.bottomLeft());
    foreach(QBgColor it, mBtnColors)
    {
        BarGradient.setColorAt(it.first,it.second);
    }

    painter->setBrush(BarGradient);

    //painter->drawRoundedRect(m_BarRect,PYSB_RECT_RADIUS,PYSB_RECT_RADIUS);
    painter->drawRect(m_BarRect);

    painter->restore();
}

void QSliderButton::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    QLinearGradient BgGradient(QPoint(0,0),QPoint(0,height()));
    //    BgGradient.setColorAt(0.0,PYSB_BG_START_COLOR);
    //    BgGradient.setColorAt(1.0,PYSB_BG_END_COLOR);
    foreach(QBgColor it, mBackColors)
    {
        BgGradient.setColorAt(it.first,it.second);
    }
    painter->setBrush(BgGradient);
    //painter->drawRoundedRect(rect(),PYSB_RECT_RADIUS,PYSB_RECT_RADIUS);
    painter->drawRect(rect());

    painter->restore();
}

void QSliderButton::drawText(QPainter *painter)
{
    painter->save();

    painter->setPen(PYSB_TEXT_COLOR);
    QFont textFont;
    textFont.setBold(true);
    painter->setFont(textFont);

    int ItemCnt = m_StrRectPairVec.count();
    qreal initX = 0;
    qreal textWidth = 0;
    QString strText;
    for(int ItemIndex = 0;ItemIndex < ItemCnt ;ItemIndex++)
    {
        //计算文字的长度与宽度
        strText = m_StrRectPairVec.at(ItemIndex).first;
        textWidth  = fontMetrics().width(strText);
        QPointF topLeft(initX,0);
        QPointF bottomRight(initX + textWidth + 2 * PYSB_EXTRA_SPACE,height());
        QRectF textRect(topLeft,bottomRight);

        m_StrRectPairVec[ItemIndex].second.rect = textRect;
        if(m_bVirgin)
        {
            m_BarRect = textRect;
            m_bVirgin = false;
        }
        //绘制文字
        painter->drawText(textRect,strText,Qt::AlignVCenter|Qt::AlignHCenter);

        /// increment initX
        //移动X轴
        initX +=textWidth + 2 * PYSB_EXTRA_SPACE;
    }

    //设置固定宽度
    // setFixedWidth(initX);
    painter->restore();
}

unsigned int QSliderButton::GetSlideIncrement()
{
    if(m_nInc > 1)
        m_nInc --;

    return m_nInc;
}

void QSliderButton::SetSlideIncrement(unsigned int nInc)
{
    m_nInc = nInc;
}

unsigned int QSliderButton::GetSlideIncrementInit(unsigned int nDistance)
{
    unsigned int n = 1;

    while(1)
    {
        if(n*n>nDistance)
            break;
        else
            n++;
    }

    return n*1.4;
}

void QSliderButton::DoSliding()
{

    qreal BarX = m_BarRect.topLeft().x();
    qreal BarWidth = m_BarRect.width();
    if(m_bForward)
    {
        BarX += GetSlideIncrement()/*PYSB_BAR_SLIDE_INCREMENT*/;
        if(BarX >= m_TargetRect.topLeft().x())
        {
            BarX = m_TargetRect.topLeft().x();
            m_slideTimer->stop();
        }
    }else{
        BarX -= GetSlideIncrement()/*PYSB_BAR_SLIDE_INCREMENT*/;
        if(BarX <= m_TargetRect.topLeft().x())
        {
            BarX = m_TargetRect.topLeft().x();
            m_slideTimer->stop();
        }
    }

    m_BarRect = QRectF(QPointF(BarX,0),QPointF(BarX + BarWidth,height()));
    update();
}

void QSliderButton::DoShrinking()
{
    qreal BarX = m_BarRect.topLeft().x();
    qreal BarWidth = m_BarRect.width();

    if(m_bShrink)
    {
        BarWidth -= PYSB_BAR_WIDTH_INCREMENT;

        if(BarWidth < m_TargetRect.width())
        {
            m_shrinkTimer->stop();
        }

    }else{
        BarWidth += PYSB_BAR_WIDTH_INCREMENT;

        if(BarWidth > m_TargetRect.width())
        {
            m_shrinkTimer->stop();
        }

    }
    m_BarRect = QRectF(QPointF(BarX,0),QPointF(BarX + BarWidth,height()));
    update();
}

//void QSliderButton::addItem(const QString &str)
//{
//   
//}

bool QSliderButton::addItem( const QString& str, QWidget* widget )
{
	if (NULL == widget)
	{
		return false;
	}
	int ItemCnt = m_StrRectPairVec.count();
	//查看是否有一样的页面
	for(int ItemIndex = 0;ItemIndex < ItemCnt ; ItemIndex++)
	{
		if(m_StrRectPairVec.at(ItemIndex).second.widget == widget)
		{
			return false;
		}
	}

	itemInfo info;
	info.rect	= QRectF();
	info.widget = widget;
	m_StrRectPairVec.push_back(qMakePair(str,info));
	update();

	if(m_StrRectPairVec.count() > 0)
	{
		//发出切换到第一页
		emit sig_itemClicked(m_StrRectPairVec.at(0).second.widget);
	}

	calcGeo();

	return true;
}

void QSliderButton::ChangePage( QWidget* widget)
{
	int ItemCnt = m_StrRectPairVec.count();
	QString strText;
	for(int ItemIndex = 0;ItemIndex < ItemCnt ; ItemIndex++)
	{
		if(m_StrRectPairVec.at(ItemIndex).second.widget == widget)
		{
			QString tmpstrText = m_StrRectPairVec.at(ItemIndex).first;
			strText = tmpstrText;
			DEBUG_VAR(strText);

			emit sig_itemClicked(m_StrRectPairVec.at(ItemIndex).second.widget);

			m_TargetRect = m_StrRectPairVec.at(ItemIndex).second.rect;

			if(m_TargetRect.width() > m_BarRect.width())
			{
				m_bShrink = false;
			}else{
				m_bShrink = true;
			}

			if(m_TargetRect.topLeft().x() > m_BarRect.topLeft().x() )
			{
				m_bForward = true;
			}else{
				m_bForward = false;
			}

			int distance = m_TargetRect.topLeft().x() - m_BarRect.topLeft().x();
			if(distance < 0)
				distance = 0 - distance;

			QString tmp = QString("%1").arg(distance);
			DEBUG_VAR(tmp);


			SetSlideIncrement(GetSlideIncrementInit((unsigned int)distance)/*PYSB_BAR_SLIDE_INCREMENT_INIT*/);
			m_slideTimer->start();
			FIREUP_SHRINK_TIMER;
		}
	}
	update();
}
