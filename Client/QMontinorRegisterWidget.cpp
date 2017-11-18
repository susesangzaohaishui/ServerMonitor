#include "QMontinorRegisterWidget.h"
#include "8Predis.h"
#include "QRedisCallBack.h"
#include "stringutil.h"
#include "NodeManager.h"
#include "QHBoxLayout"
#include "ProcessLogWidget.h"
#include "QAnimalTabWidget.h"
#include "RedeMeWidget.h"

QMontinorRegisterWidget::QMontinorRegisterWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    m_RedisCallBack = new QRedisCallBack;
    m_Redis = ProcessCtrClientRedis::CreateInstence();
    m_Redis->SetObserver(m_RedisCallBack);

    m_NodeMgr = new ProcessNodePreSerCheck(m_Redis);
    QHBoxLayout* pLayout = new QHBoxLayout;
    pLayout->addWidget(m_NodeMgr);
    ui.widget->setLayout(pLayout);

    //定时器
    m_Timer.start(10000);

  
    m_logWidget = new ProcessLogWidget(m_Redis);
    m_animalWidget = new QAnimalTabWidget;
    m_animalWidget->addItem(QString::fromWCharArray(L"进程管理"), this);
    m_animalWidget->addItem(QString::fromWCharArray(L"日志分析"), m_logWidget);
    //m_animalWidget->addItem(QString::fromWCharArray(L"使用方法"), m_pUser);

    connect(&m_Timer, SIGNAL(timeout()), this, SLOT(OnCheckLive()));
    bool ret = connect(m_RedisCallBack, SIGNAL(SigOpreate(const QString&)), this, SLOT(OnLoadRedis(const QString&)));
    ret = connect(m_NodeMgr, SIGNAL(sigLogQuery(const QString& , const QString& )), this, SLOT(OnQueryLog(const QString& , const QString&)));
}

QMontinorRegisterWidget::~QMontinorRegisterWidget()
{

}

void QMontinorRegisterWidget::OnLoadRedis( const QString& sRedis )
{
    //上图显示
    //查询redis数据
    redis_process_state bates;
    char* buf = NULL;

    if(m_Redis->QueryHostProcessTstates(sRedis, &buf))
    {
        if (buf)
        {
            memcpy(&bates, buf, sizeof(redis_process_state));
            m_NodeMgr->AddNode(bates.ip, ConvertGBKToUtf8(bates.ppath).c_str(), bates.pid, bates.memcount, bates.state);
            delete[] buf;
        }
    }
    m_NodeMgr->expandAll();
}

void QMontinorRegisterWidget::OnCheckLive()
{
    m_NodeMgr->Check();
    m_Redis->ConnectRedis();

}

void QMontinorRegisterWidget::OnQueryLog( const QString& sProcess, const QString& sIp )
{
    m_animalWidget->ChangWidget(m_logWidget);
    m_logWidget->OnQueryByUser(sProcess.toLocal8Bit().data(), sIp.toLocal8Bit().data());
}
