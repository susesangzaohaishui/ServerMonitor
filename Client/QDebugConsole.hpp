#ifndef QDEBUGCONSOLE_HPP
#define QDEBUGCONSOLE_HPP

#include <QPlainTextEdit>

class QDebugConsole : public QPlainTextEdit
{
    Q_OBJECT

signals:
    void emitData(const QByteArray &data);

public:
    explicit QDebugConsole(QWidget *parent = 0);

    void putData(const QByteArray &data);

    void setLocalEchoEnabled(bool set);

    static QDebugConsole* createInstence(QWidget* parent = 0);
    static void release();
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg);
#else
    void outputMessage(QtMsgType type, const QString &msg);
#endif
protected:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseDoubleClickEvent(QMouseEvent *e);
    virtual void contextMenuEvent(QContextMenuEvent *e);

private:
    bool localEchoEnabled;
     static QDebugConsole* mInstence_;

};

#endif // QDEBUGQDebugConsole_HPP
