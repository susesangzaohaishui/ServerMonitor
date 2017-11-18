#ifndef MAINHEADER_HPP
#define MAINHEADER_HPP


/**
  *@brief: ±ÍÃ‚¿∏
  *
  *@param:
  *
  *@author: zhaoHP
  *
  *@date: 2016/10/22
  */

#include <QWidget>
#include "ui_mainheader.h"

class MainHeader : public QWidget
{
    Q_OBJECT
public:
    explicit MainHeader(QWidget *parent = 0);
    virtual void paintEvent(QPaintEvent *);
    void setHeaderText(const QString& );
signals:
    void sigMove(QPoint&);
    void sigShowLight();
    void sigShowRight();
public slots:


private:
    Ui::MainHeader ui;


};

#endif // MAINHEADER_HPP
