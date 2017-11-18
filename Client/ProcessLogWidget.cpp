#include "ProcessLogWidget.h"
#include "8Predis.h"
#include "stringutil.h"
#include "LogItemManager.h"
#include <sstream>
#include <time.h>

#include <QHBoxLayout>

ProcessLogWidget::ProcessLogWidget(ProcessCtrClientRedis* Log_, QWidget *parent)
    : QWidget(parent),
    m_RedisLog(Log_)
{
    ui.setupUi(this);

     m_Log = new LogItemManager();
    QHBoxLayout* pHBox = new QHBoxLayout;
    pHBox->addWidget(m_Log);
    ui.widget->setLayout(pHBox);

    connect(ui.pushButton, SIGNAL(clicked(bool)), this, SLOT(OnQuery()));
    connect(ui.pushButton_2, SIGNAL(clicked(bool)), this, SLOT(OnClearLog()));
}

ProcessLogWidget::~ProcessLogWidget()
{

}
static std::string get_processname(const string& _process_name)
{
    string sret = _process_name.substr(_process_name.rfind('\\') + 1, _process_name.size());
    return sret;
}
void ProcessLogWidget::OnQueryByUser( const string& sProcess , const string& sIp, long lstart /*= -1*/, long lend /*= -1*/ )
{
    ui.lineEdit_2->setText(sIp.c_str());
    ui.lineEdit->setText( get_processname(sProcess).c_str());
    ui.checkBox->setCheckState(Qt::Unchecked);

    QueryLog(ConvertUtf8ToGBK(get_processname(sProcess).c_str()), sIp);
}

void ProcessLogWidget::QueryLog( const string& sProcess, const string& sIp, long lstart /*= -1*/, long lend /*= -1*/ )
{
    if (m_RedisLog)
    {
         vector<montior_log_redis> logs_;
         m_RedisLog->QueryLogs(sProcess, sIp, lstart, lend, logs_);

         m_Log->clearNode();

        //设置日志信息到界面
         vector<montior_log_redis>::iterator it = logs_.begin();

         for ( ; it != logs_.end(); ++it)
         {
             m_Log->addNode(*it);
         }
         m_Log->expandAll();
    }
}

static unsigned long ConvertStringToTimeLong(const string& dateStr)
{
    char buf[64];
    tm t;
    memset(&t,0,sizeof(tm));
    sscanf(dateStr.c_str(), "%[^\t]", buf, 64);
    sscanf(buf,"%04d-%02d-%02dT%02d:%02d:%02d", &t.tm_year, &t.tm_mon, &t.tm_mday, &t.tm_hour, &t.tm_min, &t.tm_sec);
    t.tm_year = t.tm_year - 1900;
    t.tm_mon = t.tm_mon - 1;
    t.tm_isdst = 0;
    return mktime(&t);
}


void ProcessLogWidget::OnQuery()
{
    QString sProcess = ui.lineEdit->text();
    QString sIp = ui.lineEdit_2->text();

    long lStart = -1;
    long lEnd = -1;
    if (ui.checkBox->checkState() == Qt::Checked)
    {
        string sStartTime = ui.dateTimeEdit->dateTime().toString(Qt::ISODate).toLocal8Bit();
        string sEndTime = ui.dateTimeEdit_2->dateTime().toString(Qt::ISODate).toLocal8Bit();

            //stringstream ssSatrt;
            //ssSatrt<<sStartTime;
       lStart =  ConvertStringToTimeLong(sStartTime);
       lEnd =  ConvertStringToTimeLong(sEndTime);
            //stringstream ssEnd;
            //ssEnd<<sEndTime;

            //ssSatrt>>lStart;
            //ssEnd>>lEnd;

    }
     QueryLog(
         ConvertUtf8ToGBK(get_processname(sProcess.toLocal8Bit().data()).c_str()),
         sIp.toLocal8Bit().data(),
         lStart,
         lEnd);
}

void ProcessLogWidget::OnClearLog()
{
    QString sProcess = ui.lineEdit->text();
    QString sIp = ui.lineEdit_2->text();

    if (sProcess != "" &&
        sIp != "") 
    {
        

       bool ret =  m_RedisLog->ClearLogs(
            ConvertUtf8ToGBK(get_processname(sProcess.toLocal8Bit().data()).c_str()),
            sIp.toLocal8Bit().data());

       if (ret)
       {
            m_Log->clearNode();
       }
    }
}
