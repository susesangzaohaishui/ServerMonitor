#ifndef QMONTINORREGISTERWIDGET_H
#define QMONTINORREGISTERWIDGET_H

#include <QWidget>
#include <QTimer>
#include "ui_QMontinorRegisterWidget.h"

class ProcessCtrClientRedis;
class QRedisCallBack;
class ProcessNodePreSerCheck;

class ProcessLogWidget;
class RedeMeWidget;
class QAnimalTabWidget;

class QMontinorRegisterWidget : public QWidget
{
    Q_OBJECT

public:
    QMontinorRegisterWidget(QWidget *parent = 0);
    ~QMontinorRegisterWidget();

private slots:
       void OnLoadRedis(const QString& sRedis);
       void OnCheckLive();
       void OnQueryLog(const QString& sProcess, const QString& sIp);

private:
    Ui::QMontinorRegisterWidget ui;

    ProcessCtrClientRedis*  m_Redis;
    QRedisCallBack*         m_RedisCallBack;
    ProcessNodePreSerCheck* m_NodeMgr;
    QTimer                  m_Timer;
public:

    RedeMeWidget* m_pUser;
    ProcessLogWidget* m_logWidget;
    QAnimalTabWidget* m_animalWidget;

};

#endif // QMONTINORREGISTERWIDGET_H
