// OurZZLLStatusComponent.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "NodeMonitorCompoent.h"
#include "IMainServiceControl.h"
#include "daemon_client_t.h"

extern IMainServiceControl* g_MainAttmpter = NULL;
NodeMonitorCompoent * g_Component = NULL;

/************************************************************************
*名  称：组件创建实例函数
*说  明：框架通过此函数对组件实例化
*参  数：无                                                                    
*返回值：服务组件类
************************************************************************/
extern "C" __declspec(dllexport) void* CreateComponentInstance()
{
	if (g_Component == NULL)
	{
		g_Component = new NodeMonitorCompoent;
	}
	return g_Component;
}

/************************************************************************
*名  称：释放组件实例 
*说  明：框架退出时调用此函数
*参  数：无                                                                    
*返回值：无
************************************************************************/
extern "C" __declspec(dllexport) void DestroyComponentInstance()
{
	if (g_Component != NULL)
	{
		delete g_Component;
		g_Component = NULL;
	}
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 OurZZLLStatusComponent.h
NodeMonitorCompoent::NodeMonitorCompoent()
{
    dahlia::daemon_client_t*   _global_client = new dahlia::daemon_client_t;
    _global_client->create_monitor();
	return;
}

void NodeMonitorCompoent::OnInitialization( const IMainServiceControl* ptrMainServiceControl )
{
	g_MainAttmpter = const_cast<IMainServiceControl*>(ptrMainServiceControl);
	
}

void NodeMonitorCompoent::OnRelease()
{
}

IInterface* NodeMonitorCompoent::QueryInterface( std::string interfaceID )
{

	return NULL;
}

std::string NodeMonitorCompoent::GetComponentID()
{
	return std::string("NodeMonitorCompoentJKLHKLHKJGJTFGVBJFYTFCHGFY");
}

void NodeMonitorCompoent::OnMessage( std::string topic, void* buf, unsigned int length )
{

}
