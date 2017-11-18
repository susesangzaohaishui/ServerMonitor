#include "QDebugConsole.hpp"

#include <QScrollBar>
#include <QDate>
#include <QtCore/QDebug>


QDebugConsole* QDebugConsole::mInstence_ = NULL;

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
static void handleMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QDebugConsole::createInstence()->outputMessage(type, context, msg);
}
#else
static void handleMessage(QtMsgType type, const char *msg)
{
    QDebugConsole::createInstence()->outputMessage(type, msg);
}
#endif
QDebugConsole::QDebugConsole(QWidget *parent)
    : QPlainTextEdit(parent)
    , localEchoEnabled(false)
{
    document()->setMaximumBlockCount(100);

    setAutoFillBackground(true);

    QPalette p = palette();
    p.setColor(QPalette::Text, Qt::green);
    setPalette(p);

   // this->setEnabled(false);
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    qInstallMessageHandler(handleMessage);
#else
    qInstallMsgHandler(handleMessage);
#endif
}

void QDebugConsole::putData(const QByteArray &data)
{
    QString strLog = QString::fromLocal8Bit(data.data());
    appendPlainText(strLog);

    QScrollBar *bar = verticalScrollBar();
    bar->setValue(bar->maximum());
}

void QDebugConsole::setLocalEchoEnabled(bool set)
{
    localEchoEnabled = set;
}

QDebugConsole *QDebugConsole::createInstence(QWidget* parent)
{
   if(NULL == QDebugConsole::mInstence_)
   {
        mInstence_ = new QDebugConsole(parent);
   }
   if(NULL != parent)
   {
       QDebugConsole::mInstence_->setParent(parent);
   }
   return  QDebugConsole::mInstence_;
}

void QDebugConsole::release()
{
    if(NULL != QDebugConsole::mInstence_)
    {
         //delete mInstence_;
    }
}

void QDebugConsole::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_Backspace:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
        break;
    default:
        if (localEchoEnabled)
            QPlainTextEdit::keyPressEvent(e);
        emit emitData(e->text().toLocal8Bit());
    }
}

void QDebugConsole::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    //setFocus();
    QPlainTextEdit::mousePressEvent(e);
}

void QDebugConsole::mouseDoubleClickEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
}

void QDebugConsole::contextMenuEvent(QContextMenuEvent *e)
{
    Q_UNUSED(e)
    //QPlainTextEdit::contextMenuEvent(e);

}
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
void QDebugConsole::outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString message;
    message = QDateTime::currentDateTime().toString("hh:mm:ss");
    switch(type)
    {
    case QtDebugMsg:
        message += QString::fromLocal8Bit(" 调试:> ");
        break;
    case QtWarningMsg:
        message += QString::fromLocal8Bit(" 警告:> ");
        break;
    case QtCriticalMsg:
        message += QString::fromLocal8Bit(" 严重:> ");
        break;
    case QtFatalMsg:
        message += QString::fromLocal8Bit(" 致命:> ");
    }

    message.append(msg);
    QByteArray array = message.toLocal8Bit();
    putData(array);
}
#else
void QDebugConsole::outputMessage(QtMsgType type, const QString &msg)
{
    QString message;
    message = QDateTime::currentDateTime().toString("hh:mm:ss");
    switch(type)
    {
    case QtDebugMsg:
        message += QString::fromWCharArray(L" 调试:> ");
        break;
    case QtWarningMsg:
        message += QString::fromWCharArray(L" 警告:> ");
        break;
    case QtCriticalMsg:
        message += QString::fromWCharArray(L" 严重:> ");
        break;
    case QtFatalMsg:
        message += QString::fromWCharArray(L" 致命:> ");
    }

    message.append(msg);
    QByteArray array = message.toLocal8Bit();
    putData(array);
}
#endif
