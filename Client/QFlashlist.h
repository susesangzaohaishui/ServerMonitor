#ifndef QFLASH_LIST_Y8_H
#define QFLASH_LIST_Y8_H

/**
  *@brief: 列表窗口
  *
  *@param:
  *
  *@author: zhaoHP
  *
  *@date: 2016/10/22
  */

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QHBoxLayout>
#include <QScrollBar>
#include <QTimer>

#define ITEM_START_ANGLE 270
#define ITEM_D_ANGLE 2
#define ITEM_D_ZOOMING_FACTOR 0.05
#define UPDATE_TIMER_INTERVAL 10 // ms
#define ITEM_COUNTER_TIMER_INTERVAL 200
#define SIZE_HINT QSize(300,300)

#define ITEM_HEIGHT 40
#define BG_START_COLOR QColor(18,25,34)
#define BG_END_COLOR QColor(18,25,34)

#define ITEM_START_COLOR ITEM_END_COLOR.lighter()
#define ITEM_END_COLOR QColor(62,135,166)

#define ITEM_START_COLOR_A QColor(250,250,250)
#define ITEM_END_COLOR_A QColor(250,250,250)

#define HOVER_OPACITY 0.2
#define HOVER_START_COLOR QColor(220,220,220)
#define HOVER_END_COLOR QColor(220,220,220)

#define HOVER_TEXT_COLOR QColor(24, 166, 130)
#define SELECT_TEXT_COLOR Qt::white
#define NORMAL_TEXT_COLOR Qt::black

#define RECT_RADIUS 4

class ItemInfo
{
public:
    ItemInfo(const QString& str):m_strData(str),m_Angle(ITEM_START_ANGLE),m_ZoomingFactor(0),m_Data(-1){}
    ItemInfo():m_Angle(ITEM_START_ANGLE),m_ZoomingFactor(0){}
    ~ItemInfo(){}

public:
    /// public interfaces
    void setText(const QString& str)
    {
        m_strData = str;
    }
	
    QString getText() const
    {
        return m_strData;
    }
	void setData(long data)
	{
		m_Data = data;
	}
	long getData() const
	{
		return m_Data;
	}
    void updateAngle()
    {
        m_Angle += ITEM_D_ANGLE;

        if(m_Angle >  360)
        {
            m_Angle = 0;
        }
    }

    void updateZoomingFactor()
    {
        m_ZoomingFactor += ITEM_D_ZOOMING_FACTOR;

        if(m_ZoomingFactor > 1.0)
        {
            m_ZoomingFactor = 1.0;
        }
    }

    bool jobDone() const
    {
        return m_Angle == 360 || m_ZoomingFactor == 1.0;
    }

    void resetAngle()
    {
        m_Angle = ITEM_START_ANGLE;
    }

    void resetZoomingFactor()
    {
        m_ZoomingFactor = 0.0;
    }

    qreal getAngle() const
    {
        return m_Angle;
    }

    qreal getZoomingFactor() const
    {
        return m_ZoomingFactor;
    }

    bool inWrongPosition() const
    {
        return m_Angle > ITEM_START_ANGLE && m_Angle < 360;
    }

    bool inWrongZoomingPosition()
    {
        return m_ZoomingFactor < 1.0;
    }

private:
    QString m_strData;
    qreal m_Angle;
    qreal m_ZoomingFactor;
	long m_Data;
};
class QFlashListAgency : public QWidget
{
	Q_OBJECT
public:
	explicit QFlashListAgency(QWidget *parent = 0);

public:
	/// public interfaces
	void addItem(const QString& str, long lData_);
	void clear();
	void setPressIndex(int nIndex);//设置当前点击的item
	void render();
	void flashItems();
    void clearPressRect()//清除点击Item
    {
        m_PressRect = QRectF();
    }

	public Q_SLOTS:
		void setCurrentIndex(int curIndex);



protected:
	void paintEvent(QPaintEvent *);

	void mouseMoveEvent(QMouseEvent *);

	void mousePressEvent(QMouseEvent *);

	void resizeEvent(QResizeEvent *);

	void leaveEvent(QEvent *);

	void showEvent(QShowEvent *);

	void wheelEvent(QWheelEvent *);

private:
	/// painting functions
	void drawBg(QPainter* painter);

	void drawItems(QPainter* painter);

	void drawHoverRect(QPainter* painter);

	void drawPressRect(QPainter* painter);

private:
	/// private utility functoins
	void initVars();
	void initSettings();
	void calcGeo();
	void makeupJobs();
	void wheelUp();
	void wheelDown();

private:
	QVector<ItemInfo> m_IIVec;

	int m_currIndex;
	int m_preIndex;//当前点击的位置
	int m_selectedIndex;
	int m_VisibleItemCnt;
	int m_ItemCounter;

	bool m_bAllJobsDone;
	bool m_FastSetIndex;

	QRectF m_HoverRect;
	QRectF m_PressRect;//当前点击的区域


	QString m_strHoverText;
	QString m_PressText;//点击区域的文字

	QTimer* m_RotateTimer;
	QTimer* m_ItemCountTimer;

	private Q_SLOTS:
		void DoRotation();
		void UpdateItemCount();

signals:
		void sig_setMaximum(int max);
		void sig_setCurrentIndex(int currIndex);
		void sig_itemClicked(const QString& str, long lData_);
};


class QFlashList : public QWidget
{
    Q_OBJECT
public:
    explicit QFlashList(QWidget *parent = 0);
    ~QFlashList();

public:
    /// proxy public interfaces for QFlashListAgency
    void addItem(const QString& str, long data_);
	void addItems(QStringList& strList);
	void setPressIndex(int nIndex)//设置当前点击的item
	{
		d->setPressIndex(nIndex);
	}
    void clear();

    void render();
	void flashItems()
	{
		d->flashItems();
	}

    virtual void hideEvent(QHideEvent *event)
    {
        d->clearPressRect();
    }

protected:
    QSize sizeHint() const
    {
        return QSize(SIZE_HINT);
    }

    void resizeEvent(QResizeEvent *);


private:
    /// private utility functoins
    void initVars();
    void initWgts();
    void initStgs();
    void initConns();

    void calcGeo();

private Q_SLOTS:

private:
    QHBoxLayout* mainLayout;
    QScrollBar* scrollbar;
    QFlashListAgency* d;

Q_SIGNALS:
    void sig_setCurrentIndex(int currIndex);
    void sig_itemClicked(const QString& str, long lData_);

public slots:

};


#endif // QFLASH_LIST_Y8_H
