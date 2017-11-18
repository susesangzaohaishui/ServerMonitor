#include "MainHeader.hpp"

#include <QLinearGradient>
#include <QIcon>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

MainHeader::MainHeader(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
   // ui.label->setAlignment(Qt::AlignRight);

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    QFont BoldFont("Helvetica", 14, QFont::ExtraLight, false);
#else
    QFont BoldFont("Helvetica", 12, 5, false);
#endif
    BoldFont.setBold(true);
    ui.label->setFont(BoldFont);
    QPalette pe;
    pe.setColor(QPalette::WindowText ,QColor(255,255,255));
    ui.label->setPalette(pe);
    
    ui.label_2->setPixmap(QPixmap(":image/spincursor.png"));

    //@@connect(ui.HeaderLeft, SIGNAL(clicked(bool)), this, SIGNAL(sigShowLight()));
    connect(ui.HeaderRight, SIGNAL(clicked(bool)), this, SIGNAL(sigShowRight()));
    ui.HeaderLeft->hide();
}

void MainHeader::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setPen(Qt::transparent);
    QLinearGradient lg(0, 0, 0, height());
    //lg.setColorAt(0,  QColor(45, 120, 82));
    //lg.setColorAt(0.5,  QColor(45, 120, 82));
    //lg.setColorAt(1,  QColor(45, 120, 82));

    lg.setColorAt(0,  QColor(24, 32, 46));
    lg.setColorAt(0.5,  QColor(24, 32, 46));
    lg.setColorAt(1,  QColor(24, 32, 46));

    painter.setBrush(lg);
    painter.drawRect(rect());
    // painter.fillRect(0, 0, width(), height(), QColor(65, 210, 82));
}

void MainHeader::setHeaderText(const QString & headertxt)
{
    //ui.label->setText(headertxt);
}
