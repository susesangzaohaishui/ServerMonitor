#ifndef LOGITEMMANAGER_H
#define LOGITEMMANAGER_H

#include <QWidget>
#include "ui_LogItemManager.h"
#include "globaldefine.h"
#include "QTreeWidgetItem"
class GodLogTreeItem : public QTreeWidgetItem
{
public:
    enum itemtype
    {
        EnumLogType,//标识日志类型节点
        EnumLogData,//日志数据节点
    };
    GodLogTreeItem(itemtype type = EnumLogType)
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
//日志数据节点
class ProcessLogNode:public GodLogTreeItem
{
public:
    ProcessLogNode(ProcessParentNode* parent = 0);
public:


public:
    montior_log_redis log;
};

//日志类型节点
class ProcessLogParentNode:public GodLogTreeItem
{
public:
    ProcessLogParentNode(QTreeWidget* parent = 0);
    ~ProcessLogParentNode();
public:
    void    AddNode(const montior_log_redis& log_);  //增加一个节点（进程名称和路径）
    void    clearNode();
    int     getCount();
public:
    map<QString,ProcessLogNode*>  m_SelfCheckItem;//自检Item
};

class LogItemManager : public QTreeWidget
{
    Q_OBJECT

public:
    LogItemManager(QWidget *parent = 0);
    ~LogItemManager();
    void clearNode();
    void addNode(const montior_log_redis& log_);
private:
    Ui::LogItemManager ui;
    map<LOG_TYPE, ProcessLogParentNode*> m_Nodes;
    //日志数据
    map<string, montior_log_redis> m_datas;
};

#endif // LOGITEMMANAGER_H
