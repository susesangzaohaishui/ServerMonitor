#include "MainFrame.hpp"

//#include "DataEngine.h"
#include "QAnimalTabWidget.h"
#include "QDebugConsole.hpp"
#include "RedeMeWidget.h"
#include "QMontinorRegisterWidget.h"
#include "ProcessLogWidget.h"
#include <QTextCodec>
#include <QFile>
#include <QtGui/QApplication>

QString getQssFromFile(QString filename)
{
    QFile f(filename);
    QString qss = "";
    if (f.open(QFile::ReadOnly))
    {
        qss = QLatin1String(f.readAll());
        f.close();
    }
    return qss;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


#if defined(_MSC_VER)||defined(_WIN32)
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#else
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#endif



    QMontinorRegisterWidget* pRegister = new QMontinorRegisterWidget;
    RedeMeWidget*  m_pUser = new RedeMeWidget;


    MainFrame w;
    w.addCenterWidget(QString::fromWCharArray(L"进程管理"), "downloadWidget", 1, eWidgetEmbed, pRegister->m_animalWidget);
    w.addCenterWidget(QString::fromWCharArray(L"使用方法"), "UserWidget", 2, eWidgetEmbed, m_pUser);
    w.show();
    qApp->setStyleSheet(getQssFromFile(":/qss/qss/abc.qss"));
    return a.exec();
}
