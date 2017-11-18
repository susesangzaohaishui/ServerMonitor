#include "LogItemManager.h"
#include "stringutil.h"
#include <sstream>
LogItemManager::LogItemManager(QWidget *parent)
    : QTreeWidget(parent)
{
    //ui.setupUi(this);

    QStringList headers;
    headers<<QString::fromWCharArray(L"日志类型")<<QString::fromWCharArray(L"时间")
        <<QString::fromWCharArray(L"附带数据");

    setColumnCount(headers.size());
    setHeaderLabels(headers);

    this->setColumnWidth(0, 120);
    this->setColumnWidth(1, 260);
    this->setColumnWidth(2, 100);

}

LogItemManager::~LogItemManager()
{

}

static QString GetStateText(LOG_TYPE state)
{
   switch (state)
   {
   case AUTO_START:
       {
           return QString::fromWCharArray(L"自动重启");
       }
   	break;
   case UNAUTO_START:
       {
           return QString::fromWCharArray(L"手动重启");
       }
       break;
   case ASSERTING_:
       {
           return QString::fromWCharArray(L"断言");
       }
       break;
   case HEART_OUTTM:
       {
           return QString::fromWCharArray(L"心跳超时");

       }
       break;
   case UNAUTO_DIE_:
       {
           return QString::fromWCharArray(L"手动关闭");

       }
       break;
   case AUTO_DIE:
       {
           return QString::fromWCharArray(L"自动重启");
       }
       break;
   }
   return QString::fromWCharArray(L"未知");
}
void LogItemManager::addNode( const montior_log_redis& log_ )
{
    stringstream ss;
    ss <<log_.s_ip;
    ss <<":";
    ss <<log_.s_process;
    ss << ":";
    ss <<(log_.log_state);
    ss <<":";
    ss <<log_.s_time;
    
    string sKey;
    ss >>sKey;

    sKey = ConvertGBKToUtf8(sKey);
    map<LOG_TYPE, ProcessLogParentNode*>::iterator it =  m_Nodes.find(log_.log_state);
    if (it == m_Nodes.end())
    {

         m_datas[sKey] = log_;
         ProcessLogParentNode* pNode = new ProcessLogParentNode();
         pNode->AddNode(log_);
         m_Nodes[log_.log_state] = pNode;
        int nCount =  pNode->getCount();

        QString sText = GetStateText(log_.log_state);
        sText += "(";
        sText += QString::number(nCount);
        sText += ")";
        pNode->setText(0, sText);

        this->addTopLevelItem(pNode);
    }
    else
    {
        it->second->AddNode(log_);

        int nCount =   it->second->getCount();
        QString sText = GetStateText(log_.log_state);
        sText += "(";
        sText += QString::number(nCount);
        sText += ")";
         it->second->setText(0, sText);
    }
}

void LogItemManager::clearNode()
{

    map<LOG_TYPE, ProcessLogParentNode*>::iterator it =  m_Nodes.begin();
    for ( ;it != m_Nodes.end(); ++it)
    {
        delete it->second;
    }
    m_Nodes.clear();
}

ProcessLogParentNode::~ProcessLogParentNode()
{
    map<QString,ProcessLogNode*>::iterator it =  m_SelfCheckItem.begin();
    for ( ;it != m_SelfCheckItem.end(); ++it)
    {
        delete it->second;
    }
    m_SelfCheckItem.clear();
}



void ProcessLogParentNode::AddNode( const montior_log_redis& log_ )
{
    //

    stringstream ss;
    ss <<log_.s_ip;
    ss <<":";
    ss <<log_.s_process;
    ss << ":";
    ss <<(log_.log_state);
    ss <<":";
    ss <<log_.s_time;

    string sKey;
    ss >>sKey;

    sKey = ConvertGBKToUtf8(sKey);

    map<QString,ProcessLogNode*>::iterator it =  m_SelfCheckItem.find(sKey.c_str());
    if (it == m_SelfCheckItem.end())
    {
        ProcessLogNode* pNode = new ProcessLogNode;
        pNode->log = log_;

        pNode->setText(1, CovertSysTime(toSystemTimes(log_.s_time)).c_str());
        this->addChild(pNode);

        m_SelfCheckItem[sKey.c_str()] = pNode;
    }

}

void ProcessLogParentNode::clearNode()
{

}

ProcessLogParentNode::ProcessLogParentNode( QTreeWidget* parent /*= 0*/ )
{

}

int ProcessLogParentNode::getCount()
{
    return m_SelfCheckItem.size();
}

ProcessLogNode::ProcessLogNode( ProcessParentNode* parent /*= 0*/ )
{

}
