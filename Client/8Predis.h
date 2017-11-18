
/************************************************************************
*	特殊声明:															$
*		行动控制redis客户端操作定义										$
*	项目名称:南部-电抗行动监控											$
*	描述:																$
*	版权:																$
*	参考:行动监控干货设计.doc												$
***********************************************************************
* $ID: ActionCtrRedis.h 2017-3-5 16:27 zhp								$
* $DATE: 2017-3-5 16:27													$
* $REVERSVERION: 0														$
* $HEAD_URL:https://nb111/svn/NBLZ/NBLZ_XDKZ/include/NB_XDKZ/			$
* ActionCtrRedis.h														$
************************************************************************/

#pragma once

#include <stdint.h>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <QString>
#include "globaldefine.h"

#ifdef PROCESSL_REDIS_EXPORTS
#define ACTCTRL_REDIS_API __declspec(dllexport)
#else
#define ACTCTRL_REDIS_API __declspec(dllimport)
#endif

namespace dahlia{
    class nb_mutex_t;
}
using namespace std;

//using namespace ;
class  CPMonQueryClientObserver
{
public:
    //响应执行方案变化,iChangeType 0:停止执行,1:开始执行
    virtual void OnOpreateChange( std::string strFANM , int iChangeType ) = 0;

};

namespace acl
{
    class IDataService;
};

class ProcessCtrClientRedis
{
public:
    ProcessCtrClientRedis();
    ~ProcessCtrClientRedis(void);

    bool SetObserver(CPMonQueryClientObserver* observer);

    //初始化redis
    bool InitRedis();

    static ProcessCtrClientRedis* CreateInstence();

    bool ConnectRedis();

    //加载配置
    bool LoadConfig();

    //通过本地配置获取
    bool LoadConfigByLocal();

    void PublishMsg( const char* szChannel,const char* szMsg );
    //void Test();
    bool ClearChannels(const string& sChannel);

    //将操作推送到redis
    bool SendOpreate(const opreate_process& opreate);
    //查询主机的进程状态
    //bool QueryHostProcessTstates(vector<HeartBate>& );
    bool QueryHostProcessTstates(const QString& sKey, char** );

    //查询日志信息
    bool QueryLogs( const string& sProcess, const string& sIp, long lStart, long lEnd , vector<montior_log_redis>&);
    bool ClearLogs(const string& sProcess, const string& sIp);
public:
    uint64_t	m_LastConnectTick;//最近一次连接时间
    static string		m_ServiceIp;
    static int			m_ServicePort;
public:
    static ProcessCtrClientRedis* m_Instence;
    acl::IDataService* m_pRedis;
    dahlia::nb_mutex_t*		m_RedisLock;//创建实例锁
    static acl::IDataService* m_pSubRedis;

};

