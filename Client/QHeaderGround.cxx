#include "QHeaderGround.hpp"
#include "ui_QHeaderGround.h"

#include <QTextLayout>
#include <QLinearGradient>
#include <QPainter>

QHeaderGround::QHeaderGround(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QHeaderGround)
{
    ui->setupUi(this);
    ui->verticalLayout_2->setContentsMargins(0, 0, 0, 0);
    mBackImage = QPixmap(":/image/resource_image/Width.png");
}

QHeaderGround::~QHeaderGround()
{
    delete ui;
}

void QHeaderGround::paintEvent(QPaintEvent *event)
{
    //设置头背景图片
    QWidget::paintEvent(event);


    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), mBackImage);

    //绘制用户头像外边框
    //在1/3处,y在1/2处
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing);
    int drawX = width() / 3;
    int drawY = height() / 2;
    painter.translate(drawX, drawY);

    //绘制LOGO外边框
    QLinearGradient lg1;
    lg1.setColorAt(0, QColor(255, 255, 255));
    lg1.setColorAt(1, QColor(255, 255, 255));
    painter.setBrush(lg1);
    int radius = 29;
    painter.drawEllipse(-radius, -radius, radius<<1, radius<<1);


    //绘制LOGO头像
    radius -= 4;
    QPixmap tmpPix(":/image/resource_image/User.png");
    painter.setBrush(tmpPix);
    painter.drawEllipse(-radius, -radius, radius<<1, radius<<1);

    //绘制文字
    QFont BoldFont;
    BoldFont.setBold(true);
    painter.setFont(BoldFont);

    painter.setPen(HOVER_TEXT_COLOR);

    QFontMetrics fontMetrics = painter.fontMetrics();

    bool didElide = false;
    int lineSpacing = fontMetrics.lineSpacing();
    int y = 0;

    //应该使用mUserName
    QTextLayout textLayout(mUserName, painter.font());
    textLayout.beginLayout();
    forever {
        QTextLine line = textLayout.createLine();

        if (!line.isValid())
            break;

        //文字绘制宽度
        line.setLineWidth(124);
        int nextLineY = y + lineSpacing;

        //文字绘制高度
        if (25 >= nextLineY + lineSpacing) {
            line.draw(&painter, QPoint(0, y));
            y = nextLineY;
            //! [2]
            //! [3]
        } else {
            QString lastLine = mUserName.mid(line.textStart());
            QString elidedLastLine = fontMetrics.elidedText(lastLine, Qt::ElideRight, width());
            painter.drawText(QPoint(-28, y + 32 + fontMetrics.ascent()), elidedLastLine);
            line = textLayout.createLine();
            didElide = line.isValid();
            break;
        }
    }
    textLayout.endLayout();
}
void QHeaderGround::setHeadBackPng(QString &strBackPng)
{
    mBackImage = QPixmap(strBackPng);
}
