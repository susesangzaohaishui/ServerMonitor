#ifndef PROCESSNODEPRESERCHECK_H
#define PROCESSNODEPRESERCHECK_H

#include <QWidget>
#include <QIcon>
#include <QTreeWidgetItem>
#include "windows.h"
#include "globaldefine.h"
#include "8Predis.h"
#include <map>
#include < QList >
#include <QAction>
#include "stdio.h"
#pragma comment(lib, "Advapi32")
using namespace std;

class GodTreeItem : public QTreeWidgetItem
{
public:
    enum itemtype
    {
        EnumParent,//父节点
        EnumProcess,//进程节点
    };
    GodTreeItem(itemtype type = EnumParent)
    {
        m_Type = type;
    }
    //获取节点类型
    itemtype GetType()
    {
        return m_Type;
    }
protected:
    itemtype m_Type;
};
class ProcessParentNode;
//进程节点
class ProcessNode:public GodTreeItem
{
public:
    ProcessNode(ProcessParentNode* parent = 0);
public:
    void    InitTreeItem();                         //初始化TreeItem
    void    InitProcess(const QString& sProcessName,  ProcessParentNode* hostNode);//初始化进程
    void    SetNodeState(PROCESS_STATE  state, bool bUpTm = true);             //设置Item的状态
    void    SetMemory(int nMemory);
    void   SetPid(int nPid);
    void    SetErr(const QString& sErr);

public:
    QIcon       m_SelfCheckRes[7]; //自检状态
    QString     m_ProcessName;//进程名称
    ProcessParentNode*  m_Host;//主机
    quint64      m_clock;
};

//主机标识
class ProcessParentNode:public GodTreeItem
{
public:
    ProcessParentNode(const QString& sParentName,QTreeWidget* parent = 0);
public:
    void    InitTreeItem();                         //初始化TreeItem
    void    SetHostFlag();//设置主机IP
    bool     IsExitsProcess(const QString& sProcess);
    void    AddNode(const QString& sProcessName,int nPid, int nMemoey, PROCESS_STATE  state = STATE_UNKNUWN);  //增加一个节点（进程名称和路径）
    void    SetNodeState(const QString& sProcessName, PROCESS_STATE  state);             //设置Item的状态（进程名称和状态）
    void    SetState(PROCESS_STATE  state = STATE_UNKNUWN, bool bUpTm = true);
    void    SetErr(const QString& sProcessName, const QString& sErr);//设置报错信息（进程名称，和错误信息）
public:
    QString  m_ParentName;  //父节点名称(对应IP)
    map<QString,ProcessNode*>  m_SelfCheckItem;//自检Item
    quint64      m_clock;
    QIcon       m_SelfCheckRes[7]; //自检状态

};

//进程状态
class ProcessNodePreSerCheck : public QTreeWidget
{
    Q_OBJECT

public:
    ProcessNodePreSerCheck(ProcessCtrClientRedis* redis , QTreeWidget *parent = 0);
    ~ProcessNodePreSerCheck();
    //增加节点(主机节点，进程名称，进程路径，进程状态)
    void AddNode(const QString& sHost, const QString& sProcessName, int nPid, int nMemoey, PROCESS_STATE state = STATE_UNKNUWN);
    //进程是否是否存在1,主机不存在，2进程不存在
    int IsExitsProcess(const QString& sHost, const QString& sProcess);
    //删除主机
    int DelHost(const QString& sHost);
    //注销进程//从监视器重删除对应的节点
    int DelProcess(const QString& sHost, const QString& sProcess);
    int Stop(const QString& sHost, const QString& sProcess);
    int Start(const QString& sHost, const QString& sProcess);
    //检测节点信息
    void Check();

signals:
    void sigLogQuery(const QString& sProcess, const QString& sIp);
private slots:
        void onMenu(const QPoint&);
            void  onDel();
            void  onStop();
            void  onStart();
            void  onLog();
private:
    map<QString, ProcessParentNode*>    m_HostNode;
    QString m_Process;
    QString m_Ip;
    QAction* m_pAdd ;
    QAction* m_pStop;
    QAction* m_pDel;
    QAction* m_pLog;
    ProcessCtrClientRedis* m_Redis;
};

#endif // PROCESSNODEPRESERCHECK_H
