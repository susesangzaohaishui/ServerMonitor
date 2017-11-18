#include "QFlashlist.h"

QFlashList::QFlashList(QWidget *parent) :
    QWidget(parent)
{
    initVars();
    initWgts();
    initStgs();
    initConns();
}

QFlashList::~QFlashList()
{
    d->clear();
}

void QFlashList::initVars()
{
}

void QFlashList::initWgts()
{
    mainLayout = new QHBoxLayout(this);
    d = new QFlashListAgency(this);

    mainLayout->addWidget(d);
    setLayout(mainLayout);
}

void QFlashList::initStgs()
{
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);


}

void QFlashList::initConns()
{
    connect(d,SIGNAL(sig_itemClicked(QString, long)),this,SIGNAL(sig_itemClicked(QString, long)));
}

void QFlashList::calcGeo()
{

}



void QFlashList::resizeEvent(QResizeEvent *)
{

}


void QFlashList::addItem(const QString &str, long data_)
{
    d->addItem(str, data_);
}

void QFlashList::clear()
{
    d->clear();
}

void QFlashList::render()
{
    d->render();
}

void QFlashList::addItems( QStringList& strList )
{
	int nIndex = 0;
	foreach(QString strItem, strList)
	{
		addItem(strItem, nIndex);
		++nIndex;
	}
}


QFlashListAgency::QFlashListAgency(QWidget* parent):QWidget(parent),m_FastSetIndex(true)
{
   initVars();
   initSettings();
}

void QFlashListAgency::initVars()
{
   m_currIndex = 0;
   m_VisibleItemCnt = 0;
   m_ItemCounter = 0;

   m_bAllJobsDone = false;

   m_RotateTimer = new QTimer(this);
   m_RotateTimer->setInterval(UPDATE_TIMER_INTERVAL);
   connect(m_RotateTimer,SIGNAL(timeout()),this,SLOT(DoRotation()));

   m_ItemCountTimer = new QTimer(this);
   m_ItemCountTimer->setInterval(ITEM_COUNTER_TIMER_INTERVAL);
   connect(m_ItemCountTimer,SIGNAL(timeout()),this,SLOT(UpdateItemCount()));
}

void QFlashListAgency::initSettings()
{
    setMouseTracking(this);
}

void QFlashListAgency::calcGeo()
{
    m_VisibleItemCnt = height()/ ITEM_HEIGHT + 1;
    int InvisibleItemCnt = m_IIVec.count() - m_VisibleItemCnt;

    if(InvisibleItemCnt >= 0)
    {
        emit sig_setMaximum(InvisibleItemCnt);
    }
}

void QFlashListAgency::makeupJobs()
{
    int Guard = 0;
    for(int index = m_currIndex; index < m_IIVec.count() ;index++)
    {
		if(Guard++ > m_VisibleItemCnt || 
			(index > m_IIVec.size()) ||
			(index < 0))
        {
            break;
        }

        if(!m_IIVec.at(index).jobDone())
        {
            if(!m_RotateTimer->isActive())
            {
                m_RotateTimer->start();
                m_ItemCountTimer->start();
                break ;
            }
        }
    }

    
	//重置当前索引之前的item
    for(int index = 0;index < m_currIndex ; index++)
    {
            m_IIVec[index].resetAngle();
    }

    // 重置m_VisibleItemCnt索引之后的
    if((m_currIndex + m_VisibleItemCnt) < m_IIVec.count())
    {
        for(int index  = (m_currIndex + m_VisibleItemCnt);index < m_IIVec.count();index++)
        {
                m_IIVec[index].resetAngle();
        }
    }

}

void QFlashListAgency::wheelUp()
{
    if((--m_currIndex) < 0)
    {
        m_currIndex = 0;
    }
    update();
    emit sig_setCurrentIndex(m_currIndex);
    makeupJobs();
}

void QFlashListAgency::wheelDown()
{
    if((++m_currIndex) + m_VisibleItemCnt > m_IIVec.count())
    {
        m_currIndex = m_IIVec.count() - m_VisibleItemCnt;

		m_currIndex = ((m_currIndex < 0) ? 0 : m_currIndex);
    }
    update();
    emit sig_setCurrentIndex(m_currIndex);
    makeupJobs();
}

void QFlashListAgency::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::HighQualityAntialiasing|QPainter::Antialiasing);
   // drawBg(&painter);//绘制背景颜色
    drawItems(&painter);//绘制items
    drawPressRect(&painter);//绘制当前item
    drawHoverRect(&painter);//绘制鼠标停靠的地方

}

void QFlashListAgency::mouseMoveEvent(QMouseEvent *e)
{
    if(!m_bAllJobsDone)
    {
        return ;
    }

    int ItemCnt = e->pos().y()/ITEM_HEIGHT;
    if(m_currIndex + ItemCnt < m_IIVec.count())
    {
        QPointF topLeft(0,ItemCnt*ITEM_HEIGHT);
        QPointF bottomRight(width(),(ItemCnt+1)*ITEM_HEIGHT);
        m_HoverRect = QRectF(topLeft,bottomRight);
		QString strTmp =  m_IIVec.at(m_currIndex+ItemCnt).getText();
        m_strHoverText = strTmp;
        update();
    }
}

void QFlashListAgency::mousePressEvent(QMouseEvent *e)
{
    if(!m_bAllJobsDone)
    {
        return ;
    }
    int ItemCnt = e->pos().y()/ITEM_HEIGHT;
    if(m_currIndex + ItemCnt < m_IIVec.count())
    {
        m_selectedIndex = m_currIndex + ItemCnt;
        QString strText = m_IIVec.at(m_selectedIndex).getText();
		long lData = m_IIVec.at(m_selectedIndex).getData();

        if(e->buttons() & Qt::LeftButton)
        {
            emit sig_itemClicked(strText, lData);//发送文字和位置
        }

		QPointF topLeft(0,ItemCnt*ITEM_HEIGHT);
		QPointF bottomRight(width(),(ItemCnt+1)*ITEM_HEIGHT);
		m_PressRect = QRectF(topLeft,bottomRight);
		m_FastSetIndex = false;
		m_PressText = strText;

    }
    update();
}

void QFlashListAgency::resizeEvent(QResizeEvent *)
{

    calcGeo();
    makeupJobs();
}

void QFlashListAgency::leaveEvent(QEvent *)
{
    m_HoverRect = QRectF();
    update();
}
void QFlashListAgency::showEvent(QShowEvent *)
{
    calcGeo();
}

void QFlashListAgency::wheelEvent(QWheelEvent *e)
{
    if(e->delta() > 0)
    {
        wheelUp();
    }else{
        wheelDown();
    }
    m_PressRect = QRectF ();

    if(!m_bAllJobsDone)
    {
        return ;
    }

    //滚轮事件重新更新鼠标位置文字
    int ItemCnt = e->pos().y()/ITEM_HEIGHT;
    if(m_currIndex + ItemCnt < m_IIVec.count())
    {
        QPointF topLeft(0,ItemCnt*ITEM_HEIGHT);
        QPointF bottomRight(width(),(ItemCnt+1)*ITEM_HEIGHT);
        m_HoverRect = QRectF(topLeft,bottomRight);
        QString strTmp =  m_IIVec.at(m_currIndex+ItemCnt).getText();
        m_strHoverText = strTmp;
        update();
    }

	update();
}

void QFlashListAgency::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient BgGradient(QPoint(0,0),QPoint(0,height()));
    BgGradient.setColorAt(0.0,BG_START_COLOR);
    BgGradient.setColorAt(1.0,BG_END_COLOR);
    painter->setBrush(BgGradient);
    painter->drawRect(rect());
    painter->restore();
}

void QFlashListAgency::drawItems(QPainter *painter)
{
    if(m_IIVec.count() == 0)
    {
        return ;
    }

    painter->save();

    int Guard = 0;
    qreal initY = 0;
    for(int index = m_currIndex;index < m_IIVec.count();index++)
    {
        if(Guard++ > m_VisibleItemCnt || 
			(index > m_IIVec.size()) ||
			(index < 0))
        {
            break ;
        }

        QPointF topLeft(0,initY);
        QPointF bottomRight(width(),initY + ITEM_HEIGHT);
        QRectF ItemRect(topLeft,bottomRight);

        painter->save();
        QTransform t;
        t.translate(ItemRect.center().x(),ItemRect.center().y());

        t.scale(m_IIVec.at(index).getZoomingFactor(),m_IIVec.at(index).getZoomingFactor());
        painter->setTransform(t);

        QPointF TedTopLeft(-width()/2,-ITEM_HEIGHT/2);
        QPointF TedBottomRight(width()/2,ITEM_HEIGHT/2);
        QRectF TedRect(TedTopLeft,TedBottomRight);

        QLinearGradient ItemGradient(TedRect.topLeft(),TedRect.bottomLeft());
       /* if(index%2)
        {
            ItemGradient.setColorAt(0.0,ITEM_START_COLOR);
            ItemGradient.setColorAt(1.0,ITEM_END_COLOR);
        }else*/{
            ItemGradient.setColorAt(0.0,ITEM_START_COLOR_A);
            ItemGradient.setColorAt(1.0,ITEM_END_COLOR_A);
        }
        painter->setPen(Qt::NoPen);
        painter->setBrush(ItemGradient);
        painter->drawRect(TedRect);

        painter->setPen(NORMAL_TEXT_COLOR);
        painter->drawText(TedRect,m_IIVec.at(index).getText(),Qt::AlignVCenter|Qt::AlignHCenter);
        painter->restore();
        /// increment initY
        initY += ITEM_HEIGHT;
    }
    painter->restore();
}

void QFlashListAgency::drawHoverRect(QPainter *painter)
{
    if(m_HoverRect.isEmpty() && !m_bAllJobsDone)
    {
        return ;
    }

    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient HoverGradient(m_HoverRect.topLeft(),m_HoverRect.bottomLeft());
    HoverGradient.setColorAt(0.0,HOVER_START_COLOR);
    HoverGradient.setColorAt(1.0,HOVER_END_COLOR);
    painter->setBrush(HoverGradient);
    painter->drawRoundedRect(m_HoverRect,RECT_RADIUS,RECT_RADIUS);

	QFont BoldFont("Helvetica", 18, false);
	BoldFont.setBold(true);
	painter->setFont(BoldFont);

    painter->setPen(HOVER_TEXT_COLOR);
    painter->drawText(m_HoverRect,m_strHoverText,Qt::AlignVCenter|Qt::AlignHCenter);
    painter->restore();
    //update();

}

void QFlashListAgency::drawPressRect( QPainter* painter )
{
	if(m_PressRect.isEmpty() && !m_bAllJobsDone)
	{
		return ;
	}

	painter->save();
	painter->setPen(Qt::NoPen);
	QLinearGradient HoverGradient(m_PressRect.topLeft(),m_PressRect.bottomLeft());
	HoverGradient.setColorAt(0.0,HOVER_START_COLOR);
	HoverGradient.setColorAt(1.0,HOVER_END_COLOR);
	painter->setBrush(HoverGradient);
	painter->drawRoundedRect(m_PressRect,RECT_RADIUS,RECT_RADIUS);

    QFont BoldFont;
    BoldFont.setBold(true);
    BoldFont.setWeight(56);
    painter->setFont(BoldFont);

    painter->setPen(HOVER_TEXT_COLOR);
	painter->drawText(m_PressRect,m_PressText,Qt::AlignVCenter|Qt::AlignHCenter);
	painter->restore();
}


void QFlashListAgency::DoRotation()
{
    int Guard = 0;
    bool bHasJobUndone = false;
    m_bAllJobsDone = false;
    m_HoverRect = QRectF();

    for(int index = m_currIndex;index < m_IIVec.count()/* && Guard < m_ItemCounter*/ ;index++ )
    {
        if(!m_IIVec.at(index).jobDone())
        {
            bHasJobUndone = true;
            m_IIVec[index].updateZoomingFactor();
        }

        if(Guard++ > m_VisibleItemCnt)
        {
            break;
        }
        update();
    }

    if(!bHasJobUndone)
    {
        m_RotateTimer->stop();
        m_bAllJobsDone = true;
    }

}

void QFlashListAgency::UpdateItemCount()
{
    if(++m_ItemCounter > m_VisibleItemCnt)
    {
        if(m_ItemCountTimer->isActive())
        {
            m_ItemCountTimer->stop();
            m_ItemCounter = 0;
        }
    }
}

void QFlashListAgency::addItem(const QString &str, long lData_)
{
    ItemInfo ID(str);
	ID.setData(lData_);
    m_IIVec.push_back(ID);

    if(m_RotateTimer->isActive())
    {
        m_RotateTimer->stop();
    }
    m_RotateTimer->start();

}

//设置点击的item
void QFlashListAgency::setPressIndex( int nIndex )
{
	if(m_currIndex + nIndex < m_IIVec.count())
	{
		if (m_FastSetIndex)
		{
			m_FastSetIndex = false;
			return;
		}
		m_selectedIndex = m_currIndex + nIndex;
		
		QString strText = m_IIVec.at(m_selectedIndex).getText();
		long lData = m_IIVec.at(m_selectedIndex).getData();
		emit sig_itemClicked(strText, lData);//发送文字和位置

		QPointF topLeft(0,nIndex*ITEM_HEIGHT);
		QPointF bottomRight(width(),(nIndex+1)*ITEM_HEIGHT);
		m_PressRect = QRectF(topLeft,bottomRight);
		m_PressText = strText;
		update();
	}
}



void QFlashListAgency::clear()
{

}

void QFlashListAgency::render()
{
    update();
}

void QFlashListAgency::setCurrentIndex(int curIndex)
{
    if(curIndex == m_currIndex)
    {
        return ;
    }
	m_PressRect = QRectF ();

    m_currIndex = curIndex;

    m_VisibleItemCnt = height()/ITEM_HEIGHT + 1;
    int Guard = 0;
    for(int index = m_currIndex ;index < m_IIVec.count();index++)
    {
        m_IIVec[index].resetZoomingFactor();
        if(Guard++ > m_VisibleItemCnt)
        {
            break ;
        }
    }
    m_RotateTimer->start();
    m_ItemCountTimer->start();
}

void QFlashListAgency::flashItems()
{
	if(m_RotateTimer->isActive())
	{
		m_RotateTimer->stop();
	}
	m_RotateTimer->start();
}

