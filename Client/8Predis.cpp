#include <io.h>

#include "8Predis.h"
#include "nbmutex.h"
#include "DataServiceInterface.h"
#include "NBClock.h"
#include "processmon.pb.h"
#include "dahlia_utils.h"
#include "stringutil.h"
#include <sstream>
using namespace std;

ProcessCtrClientRedis* ProcessCtrClientRedis::m_Instence = NULL;
acl::IDataService* ProcessCtrClientRedis::m_pSubRedis = NULL;
string  ProcessCtrClientRedis::m_ServiceIp = "16.5.2.117";
int	    ProcessCtrClientRedis::m_ServicePort  = 6379;
// 定义函数指针
typedef int (*CIPCPQ_GetCnctParm)(char* segPref,char* segVer,char* DBPref ,char* DBVer , char* serverIP , 
    char* DBSID , char* userName , char* userPwd , char* serviceName , char* ODBCName);
CIPCPQ_GetCnctParm m_GetCnctParm;
typedef 	void (*CIPCPQ_DllFreeMem)(void *);
CIPCPQ_DllFreeMem m_DllFreeMem;

CPMonQueryClientObserver* g_QueryObserver = NULL;

const string g_chnnel_str   = "DlmonProcess";

static int RedisCallback(string rcvChannel,string rcvMessage)
{
    //Key为:ip
    if (rcvChannel == "process_moitor")
    {
        if (g_QueryObserver)
        {
            g_QueryObserver->OnOpreateChange(rcvMessage,1);
        }
    }

    return 0;
}

//数据转移线程
UINT SubscribeMessageThreadFunc(LPVOID lpParam)
{
    if (ProcessCtrClientRedis::m_pSubRedis == NULL)
    {
        do 
        {
            ProcessCtrClientRedis::m_pSubRedis = 
                acl::ICreateDataService(
                ProcessCtrClientRedis::m_ServiceIp.c_str(),
                ProcessCtrClientRedis::m_ServicePort); 
            Sleep(3000);
        } while (ProcessCtrClientRedis::m_pSubRedis == NULL);


        char* channel="process_moitor";
        if (ProcessCtrClientRedis::m_pSubRedis)
        {
            bool ret =  ProcessCtrClientRedis::m_pSubRedis->RegistCalBakFuc(channel,RedisCallback);
            int al = 0;
        }	

        vector<string> channels;
        channels.push_back(channel);

        if (ProcessCtrClientRedis::m_pSubRedis)
        {
            ProcessCtrClientRedis::m_pSubRedis->SubscribeMessageNew(channels);  
        }

        return 1;
    }

    return -1;
}


ProcessCtrClientRedis::ProcessCtrClientRedis()
{
    m_RedisLock = new dahlia::nb_mutex_t;
    //读取配置文件
    if(LoadConfig())
    {
        if(!InitRedis())
        {
            while(!ConnectRedis())
            {
                //GetLog4Mgr().LogMsgError("数据Redis服务连接失败，10s后重连...");
                Sleep(10000);
            }
        }
    }

    // ClearChannels("ActionExeState");
}

ProcessCtrClientRedis::~ProcessCtrClientRedis(void)
{
    if (m_RedisLock)
    {
        delete m_RedisLock;
    }
}

bool ProcessCtrClientRedis::InitRedis()
{
    m_pRedis = acl::ICreateDataService(m_ServiceIp.c_str(),m_ServicePort); 
    m_LastConnectTick = nbclock::now_us() / 1000000.0; //最近一次连接时间
    if(!m_pRedis)
    {
        //GetLog4Mgr().LogMsgError("数据Redis服务连接失败，正在重连...");
        return false;
    }
    else
    {
        ////开线程订阅数据变化
        m_RedisLock->lock();

        DWORD dwThread(0);
        ::CreateThread(0,0,(LPTHREAD_START_ROUTINE)SubscribeMessageThreadFunc,m_pRedis,0,&dwThread);

        m_RedisLock->unlock();
    }
    return true;
}

bool ProcessCtrClientRedis::ConnectRedis()
{
    //检测数据连接redis
    bool bconnect_data = false;
    if (m_pRedis)
    {
        //如果连接断开
        if(!m_pRedis->IsConnected())
        {
            //如果与上次连接差值超过40s则重新连接
            if (fabs(m_LastConnectTick - nbclock::now_us() / 1000000.0) > 10.0)
            {
                m_LastConnectTick = nbclock::now_us() / 1000000.0; //更新最近一次连接时间
                m_RedisLock->lock();
                if (m_pRedis)
                {
                    m_LastConnectTick = nbclock::now_us() / 1000000.0; //更新最近一次连接时间
                    if(!m_pRedis->ReConnected())
                    {
                        //重新连接失败
                        m_RedisLock->unlock();
                        bconnect_data =  false;
                    }
                    else
                    {
                        m_RedisLock->unlock();
                        bconnect_data =  true;
                    }
                }
                m_RedisLock->unlock();
            }
        }
        else
        {
            bconnect_data =  true;
        }

    }
    else
    {
        int nDis = fabs(m_LastConnectTick - nbclock::now_us() / 1000000.0);
        if (nDis > 10.0)
        {
            m_RedisLock->lock();
            if (NULL == m_pRedis)
            {
                m_pRedis = acl::ICreateDataService(m_ServiceIp.c_str() ,m_ServicePort); 
                m_LastConnectTick = nbclock::now_us() / 1000000.0; //最近一次连接时间
                if(!m_pRedis)
                {
                    //连接失败
                    m_RedisLock->unlock();
                    bconnect_data =  false;
                }
                else
                {
                    //开线程订阅数据变化
                    DWORD dwThread(0);
                    ::CreateThread(0,0,(LPTHREAD_START_ROUTINE)SubscribeMessageThreadFunc,m_pRedis,0,&dwThread);
                    m_RedisLock->unlock();
                    bconnect_data = true;
                }
            }
            m_RedisLock->unlock();
        }
    }
    if (bconnect_data)
    {
        //if (ProcessCtrClientRedis::m_pSubRedis == NULL)
        //{
        //    bconnect_data = false;
        //}
        //else
        //{
        //  // bconnect_data =  ProcessCtrClientRedis::m_pSubRedis->ReConnected();
        //}
    }
    return bconnect_data;
}

bool ProcessCtrClientRedis::LoadConfig()
{
    string s_file = get_app_path();
    s_file = s_file + "/redisconfig.ini";

    //获取服务端口
    ProcessCtrClientRedis::m_ServicePort = GetPrivateProfileIntA("RedisServer","MemeryServerPort",6379,s_file.c_str() );

    //通过配置文件进行读取
    char s_ip[42] = {0};
    GetPrivateProfileStringA("RedisServer","ServerIP","127.0.0.1",s_ip,32,s_file.c_str());

    //通过段前缀依赖
    ProcessCtrClientRedis::m_ServiceIp = s_ip;
    return true;
}

bool ProcessCtrClientRedis::LoadConfigByLocal()
{


    return true;
}

bool ProcessCtrClientRedis::ClearChannels(const string& sChannel)
{
    if (!ConnectRedis())
    {
        return false;
    }

    if (!m_pRedis)
    {
        return false;
    }

    string strKeyPat = "*";
    vector<string> vKeys;
    m_pRedis->GetKeys(sChannel.c_str(),strKeyPat.c_str(),vKeys);

    bool bRet  = false;
    for (int i = 0; i < vKeys.size(); ++i)
    {
        string strKey = vKeys[i];
        bRet = m_pRedis->DeleteKey(sChannel.c_str(),strKey.c_str());
    }
    return bRet;
}

ProcessCtrClientRedis* ProcessCtrClientRedis::CreateInstence()
{
    if (ProcessCtrClientRedis::m_Instence == NULL)
    {
        ProcessCtrClientRedis::m_Instence = new ProcessCtrClientRedis();
    }
    return ProcessCtrClientRedis::m_Instence;
}

void ProcessCtrClientRedis::PublishMsg( const char* szChannel,const char* szMsg )
{
    if (m_pRedis)
    {
        if (NULL != szChannel && NULL != szMsg)
        {
            m_pRedis->PublishMessage(szChannel,szMsg);
        }
    }
}

bool ProcessCtrClientRedis::SendOpreate(const opreate_process& opreate)
{
    if (!ConnectRedis())
    {
        return false;
    }

    if (!m_pRedis)
    {
        return false;
    }


    string s_chnnel = g_chnnel_str;
    s_chnnel += ":process_opreate";

    stringstream ss;
    string spath = opreate.ppath;
    spath =  spath.substr(spath.rfind('\\') + 1, spath.size());
    //ss<<spath;
    ss<<"_";
    ss<<opreate.ip;
    string sKey = "";
    ss>>sKey;
    //sKey = ConvertGBKToUtf8(sKey);

    bool bRet = m_pRedis->SetBuffer(s_chnnel.c_str(),sKey.c_str() , (char*)&opreate, sizeof(opreate_process));
    m_pRedis->PublishMessage("process_opreate", sKey.c_str());
    return true;
}

bool ProcessCtrClientRedis::SetObserver( CPMonQueryClientObserver* observer )
{
    g_QueryObserver = observer;
    return true;
}

bool ProcessCtrClientRedis::QueryHostProcessTstates(const QString& sKey, char** states)
{

    string s_chnnel = g_chnnel_str;
    s_chnnel += ":process_moitor";

    unsigned int nLen = sizeof(redis_process_state);

    bool bRet = m_pRedis->GetBuffer(s_chnnel.c_str(),sKey.toLocal8Bit().data(), *states, nLen);
    if (!bRet ||
        nLen != sizeof(redis_process_state))
    {
        return false;
    }

    return true;
}

bool ProcessCtrClientRedis::QueryLogs(
    const string& sProcess,
    const string& sIp,
    long lStart, 
    long lEnd ,
    vector<montior_log_redis>& logs_)
{
    if (lStart > lEnd)
    {
        return false;
    }

    if (!ConnectRedis())
    {
        return false;
    }

    string s_chnnel = g_chnnel_str;
    s_chnnel += ":process_log";

    string sKey = sIp;
    sKey += ":";
    sKey += sProcess;
    sKey += ":*";

    vector<string> vKeys;
    m_pRedis->GetKeys(s_chnnel.c_str(),sKey.c_str(),vKeys);

    montior_log_redis log_;
    for (int i = 0; i < vKeys.size(); ++i)
    {
        MonLogMSG msg;
        string strKey = vKeys[i];
        m_pRedis->GetMessage(s_chnnel.c_str(),strKey.c_str(), &msg);

        if (lStart != -1 &&
            lEnd    != -1)
        {
            //判断时间
            int nTime =  msg.s_time();
            if(lStart <= nTime &&
                nTime <= lEnd)
            {
                log_.log_state = (LOG_TYPE)msg.log_state();
                log_.n_type = msg.n_type();
                log_.s_data_exten = msg.s_data_exten();
                log_.s_info = msg.s_info();
                log_.s_ip = msg.shost();
                log_.s_process = msg.sprocess();
                log_.s_time = msg.s_time();

                logs_.push_back(log_);
            }
        }
        else
        {
            //全部查询出来
            log_.log_state = (LOG_TYPE)msg.log_state();
            log_.n_type = msg.n_type();
            log_.s_data_exten = msg.s_data_exten();
            log_.s_info = msg.s_info();
            log_.s_ip = msg.shost();
            log_.s_process = msg.sprocess();
            log_.s_time = msg.s_time();
            logs_.push_back(log_);
        }
    }
}

bool ProcessCtrClientRedis::ClearLogs( const string& sProcess, const string& sIp )
{
    if (!ConnectRedis())
    {
        return false;
    }

    string s_chnnel = g_chnnel_str;
    s_chnnel += ":process_log";

    string sKey = sIp;
    sKey += ":";
    sKey += sProcess;
    sKey += ":*";

    return m_pRedis->DeleteKeys(s_chnnel.c_str(),sKey.c_str());

    //vector<string> vKeys;
    //m_pRedis->GetKeys("process_log",sKey.c_str(),vKeys);

    //montior_log_redis log_;
    //for (int i = 0; i < vKeys.size(); ++i)
    //{
    //     
    //}
}
