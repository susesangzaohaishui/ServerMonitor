
/**
  *@brief: ÖÐ¼ä´°¿Ú
  *
  *@param:
  *
  *@author: zhaoHP
  *
  *@date: 2016/10/22
  */

#ifndef QCENTERWIDGET_HPP
#define QCENTERWIDGET_HPP

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QWidget>
#include <QBoxLayout>
#include <QStackedWidget>
#include <QResizeEvent>
#include <QPixmap>

class QCenterWidget : public QFrame
{
    Q_OBJECT
private:
    QStackedWidget* stackWidget;
    QBoxLayout* navlayout;
    QVBoxLayout* mainLayout;
    int currentIndex;
    int preindex;
public:
    enum Alignment_Direction{
        TopLeft,
        TopCenter,
        TopRight,
        RightTop,
        RightCenter,
        RightBottom,
        BottomRight,
        BottomCenter,
        BottomLeft,
        LeftBottom,
        LeftCenter,
        LeftTop,
    };

    enum animation_Direction{
        animationTop,
        animationRight,
        animationBottom,
        animationLeft,
        animationTopLeft,
        animationTopRight,
        animationBottomRight,
        animationBottomLeft,
        animationCenter
    };

public:
    explicit QCenterWidget(QWidget *parent = 0);
    void initData();
    void initUI();
    void initConnect();
    void addWidget(const QString& tile, const QString &obejctName, QWidget* widget);
signals:
    void emitCurrrWnd(const QString&);

public slots:
    void switchscreen(const int index);
    void switchscreen(const QWidget*);
    void switchscreen();
    void swicthLayout(QBoxLayout::Direction direction);
    virtual void cloudAntimation(animation_Direction direction, const QSize& size_);
    void onChgWnd(int);

private:
    QLabel* mShowLine;

};

#endif // QCENTERWIDGET_HPP
