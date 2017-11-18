#ifndef QHEADERGROUND_HPP
#define QHEADERGROUND_HPP

/**
  *@brief: ±ÍÃ‚¿∏Õ∑
  *
  *@param:
  *
  *@author: zhaoHP
  *
  *@date: 2016/10/22
  */

#define NORMAL_TEXT_COLOR QColor(255,255,255)
#define HOVER_TEXT_COLOR QColor(255,255,255)

#include <QPixmap>
#include <QWidget>

namespace Ui {
class QHeaderGround;
}

class QHeaderGround : public QWidget
{
    Q_OBJECT

public:
    explicit QHeaderGround(QWidget *parent = 0);
    ~QHeaderGround();
    virtual void paintEvent(QPaintEvent *event);
    void setUserName(QString strName)
    {
        mUserName = strName;
    }

    void setHeadBackPng(QString &strBackPng);
private:
    Ui::QHeaderGround    *ui;
    QPixmap              mBackImage;
    QString              mUserName;
};

#endif // QHEADERGROUND_HPP
