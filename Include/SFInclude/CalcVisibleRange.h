#pragma once
#include "GlobalStruct.h"
#include "com.cetc29.rpc.service.generated.CalculateElecRange2D3D.interface.h"

class CalcVisible2D3DRange
{
public:
	CalcVisible2D3DRange(void);
	~CalcVisible2D3DRange(void);
	static CalcVisible2D3DRange* m_pCalcInstance;
	static CalcVisible2D3DRange* GetCalcInstance();
	static void ReleaseCalcInstance();

public:

	//外部调用接口，nSeaAirFlag: 0对空，1对海； calculateType：0:获取2维计算包络;1:获取三维计算包络;2:获取2，3维计算包络
	//rangeType：0,预警探测 1，侦察发现 2，定位识别
	bool CalcVisible2D3DRangeData(   int nSeaAirFlag,  int calculateType, int rangType, map<string, BaseCalcStruct::stDKRadarRange> &mapSingleEffRangle2D, SFSmartPtr<com::cetc29::rpc::service::generated::ICalculateRangeReplyOf2D3DProto> &result);

	//雷达效能通视计算接口<多个雷达包络><暂不可用>
	void CalcVisible2DRange(const vector<BaseCalcStruct::stDKRadarRange>& _vInData, vector<BaseCalcStruct::stDKRadarRange>& _vOutData );
	//雷达效能通视计算接口<暂不可用>
	void CalcVisible2DRangeOne(const BaseCalcStruct::stDKRadarRange& _stInData, BaseCalcStruct::stDKRadarRange& _stOutData);

private:

	//服务初始化
	void Init3DServer();
	//服务调用
	bool CallServer2Calc3D(SFSmartPtr<com::cetc29::rpc::service::generated::ICalculateRangeOf2D3DRequestProto> &param0, SFSmartPtr<com::cetc29::rpc::service::generated::ICalculateRangeReplyOf2D3DProto> &result);
	
	//输入数据格式转换<从内部格式转换为SF格式>
	void CovertRange2DFor3DService(map<string,BaseCalcStruct::stDKRadarRange>& vRange, SFSmartPtr<com::cetc29::rpc::service::generated::ICalculateRangeOf2D3DRequestProto>& result );

private:

	SFSmartPtr<com::cetc29::rpc::service::generated::ICalculateElecRange2D3DRPCIProto> m_pServer3D;

	SFSmartPtr<IServiceParams> m_pServiceParams;

};

