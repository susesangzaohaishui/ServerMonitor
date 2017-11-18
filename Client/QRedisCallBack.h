#ifndef QREDISCALLBACK_H
#define QREDISCALLBACK_H

#include <QObject>
#include "8Predis.h"

class QRedisCallBack : public QObject , public CPMonQueryClientObserver
{
    Q_OBJECT

public:
    QRedisCallBack(QObject *parent = NULL);
    ~QRedisCallBack();
    virtual void OnOpreateChange( std::string strFANM , int iChangeType );
private:
signals:
    void SigOpreate(const QString& );
};

#endif // QREDISCALLBACK_H
