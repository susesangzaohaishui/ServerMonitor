
/**
  *@brief: 右列表
  *
  *@param:
  *
  *@author: zhaoHP
  *
  *@date: 2016/10/22
  */

#ifndef QRightAction_HPP
#define QRightAction_HPP

#include <QWidget>

class QFlashList;

/**
 * @brief 右上角关于
 */
class QRightAction: public QWidget
{
    Q_OBJECT
public:
    QRightAction(QWidget* paren = NULL);

    virtual void focusOutEvent(QFocusEvent *event);
    void showEvent(QShowEvent *_event);

public slots:
    void onCloseAnima();
    void onItemClicked(const QString &, long);
signals:
    void sigMinSize();
protected:
    void AnimationLeft(bool flag);
private:
    QFlashList* mFlashList;
    QSize       mNormalSize;
};

#endif // QRightAction_HPP
