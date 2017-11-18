/****************************************************************************
** Meta object code from reading C++ file 'NodeManager.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../NodeManager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NodeManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ProcessNodePreSerCheck[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      37,   24,   23,   23, 0x05,

 // slots: signature, parameters, type, tag, flags
      66,   23,   23,   23, 0x08,
      81,   23,   23,   23, 0x08,
      89,   23,   23,   23, 0x08,
      98,   23,   23,   23, 0x08,
     108,   23,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ProcessNodePreSerCheck[] = {
    "ProcessNodePreSerCheck\0\0sProcess,sIp\0"
    "sigLogQuery(QString,QString)\0"
    "onMenu(QPoint)\0onDel()\0onStop()\0"
    "onStart()\0onLog()\0"
};

void ProcessNodePreSerCheck::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ProcessNodePreSerCheck *_t = static_cast<ProcessNodePreSerCheck *>(_o);
        switch (_id) {
        case 0: _t->sigLogQuery((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->onMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 2: _t->onDel(); break;
        case 3: _t->onStop(); break;
        case 4: _t->onStart(); break;
        case 5: _t->onLog(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ProcessNodePreSerCheck::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ProcessNodePreSerCheck::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_ProcessNodePreSerCheck,
      qt_meta_data_ProcessNodePreSerCheck, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ProcessNodePreSerCheck::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ProcessNodePreSerCheck::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ProcessNodePreSerCheck::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ProcessNodePreSerCheck))
        return static_cast<void*>(const_cast< ProcessNodePreSerCheck*>(this));
    return QTreeWidget::qt_metacast(_clname);
}

int ProcessNodePreSerCheck::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ProcessNodePreSerCheck::sigLogQuery(const QString & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
