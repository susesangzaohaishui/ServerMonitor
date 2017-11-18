#include "QRedisCallBack.h"

QRedisCallBack::QRedisCallBack(QObject *parent)
    : QObject(parent)
{

}

QRedisCallBack::~QRedisCallBack()
{

}

void QRedisCallBack::OnOpreateChange( std::string strFANM , int iChangeType )
{
    
    emit SigOpreate(strFANM.c_str());
}
