#ifndef RedisCondition_INCLUDED
#define RedisCondition_INCLUDED

#include <vector>

using namespace std;

#pragma pack(8)

/************************************************************************/
/* 查询模式, 包括精确、模糊和范围三种模式                                                               
/************************************************************************/ 
enum QueryMode
{
	PRECISE = 1, /// 精确查询
	FUZZY   = 2, /// 模糊查询
	RANGE   = 3  /// 范围查询
};

/************************************************************************/
/* 域数据类型, 包括字符串、整型、浮点型和日期四种类型                                                              
/************************************************************************/ 
enum FieldType
{
	STRING     = 1, ///字符串
	INTEGER    = 2, ///整型
	FLOATING   = 3, ///浮点型
	DATETIME   = 4  ///日期型
};

/************************************************************************/
/* 排序模式, 包括升序和降序两种模式                                                               
/************************************************************************/ 
enum SortMode
{
	ASC  =1, ///升序
	DESC =2  ///降序
};

typedef struct _field{
	string       m_field; /// 域值
	FieldType    m_fieldtype;/// 域类型，STRING=字符串 INTEGER=整型 FLOATING=浮点 DATETIME=日期
	string       m_timeFormat;/// 日期格式，域类型为日期时启用， 默认格式 %d-%d-%d %d:%d:%d， 例如 2015-3-2 9:39:15
} Field;

typedef struct _wherecondition{
	Field        s_field;/// 域
	QueryMode    m_queryMode;/// 查询模式，PRECISE=精确 FUZZY=模糊 RANGE=范围
	string       m_value;/// 值，查询模式为PRECISE和FUZZY时启用
	string       m_maxValue;/// 最大值，查询模式为RANGE时启用, invalid表示无效值，不参与比较
	string       m_minValue;/// 最小值，查询模式为RANGE时启用, invalid表示无效值，不参与比较
	bool         m_leftBoundary; ///是否包括左边界，查询模式为RANGE时启用
	bool         m_rightBoundary; ///是否包括右边界，查询模式为RANGE时启用
	
} WhereCondition;

typedef struct _ordercondition{
	Field    s_field;/// 域
	SortMode m_sortMode;/// 排序模式，ASC=升序 DESC=降序 
} OrderCondition;

class RedisCondition
{
public:
	vector<WhereCondition> andList;/// AND条件
	vector<WhereCondition> orList;/// OR条件
	vector<OrderCondition> orderList;/// 排序条件
};

#pragma pack()

#endif