/****************************************************************************
** Meta object code from reading C++ file 'QCenterWidget.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QCenterWidget.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QCenterWidget.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QCenterWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      43,   37,   14,   14, 0x0a,
      61,   14,   14,   14, 0x0a,
      90,   14,   14,   14, 0x0a,
     115,  105,   14,   14, 0x0a,
     167,  151,   14,   14, 0x0a,
     210,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QCenterWidget[] = {
    "QCenterWidget\0\0emitCurrrWnd(QString)\0"
    "index\0switchscreen(int)\0"
    "switchscreen(const QWidget*)\0"
    "switchscreen()\0direction\0"
    "swicthLayout(QBoxLayout::Direction)\0"
    "direction,size_\0"
    "cloudAntimation(animation_Direction,QSize)\0"
    "onChgWnd(int)\0"
};

void QCenterWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QCenterWidget *_t = static_cast<QCenterWidget *>(_o);
        switch (_id) {
        case 0: _t->emitCurrrWnd((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->switchscreen((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 2: _t->switchscreen((*reinterpret_cast< const QWidget*(*)>(_a[1]))); break;
        case 3: _t->switchscreen(); break;
        case 4: _t->swicthLayout((*reinterpret_cast< QBoxLayout::Direction(*)>(_a[1]))); break;
        case 5: _t->cloudAntimation((*reinterpret_cast< animation_Direction(*)>(_a[1])),(*reinterpret_cast< const QSize(*)>(_a[2]))); break;
        case 6: _t->onChgWnd((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QCenterWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QCenterWidget::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_QCenterWidget,
      qt_meta_data_QCenterWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QCenterWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QCenterWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QCenterWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QCenterWidget))
        return static_cast<void*>(const_cast< QCenterWidget*>(this));
    return QFrame::qt_metacast(_clname);
}

int QCenterWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void QCenterWidget::emitCurrrWnd(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
