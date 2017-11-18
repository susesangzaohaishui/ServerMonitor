#ifndef PROCESSLOGWIDGET_H
#define PROCESSLOGWIDGET_H

#include <QWidget>
#include "ui_ProcessLogWidget.h"
#include <string>
using namespace std;

class ProcessCtrClientRedis;
class LogItemManager;

class ProcessLogWidget : public QWidget
{
    Q_OBJECT

public:
    ProcessLogWidget(ProcessCtrClientRedis* Log_, QWidget *parent = 0);
    ~ProcessLogWidget();

    void OnQueryByUser(const string& sProcess, const string& sIp, long lstart = -1, long lend = -1);
private:
    Ui::ProcessLogWidget ui;
    ProcessCtrClientRedis* m_RedisLog;

private:
    void QueryLog(const string& sProcess, const string& sIp, long lstart = -1, long lend = -1);
private slots:
    void OnQuery();
    void OnClearLog();
private:
    LogItemManager* m_Log;
};

#endif // PROCESSLOGWIDGET_H
