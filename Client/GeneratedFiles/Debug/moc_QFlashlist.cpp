/****************************************************************************
** Meta object code from reading C++ file 'QFlashlist.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QFlashlist.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QFlashlist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QFlashListAgency[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   18,   17,   17, 0x05,
      52,   42,   17,   17, 0x05,
      88,   77,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
     127,  118,   17,   17, 0x0a,
     148,   17,   17,   17, 0x08,
     161,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QFlashListAgency[] = {
    "QFlashListAgency\0\0max\0sig_setMaximum(int)\0"
    "currIndex\0sig_setCurrentIndex(int)\0"
    "str,lData_\0sig_itemClicked(QString,long)\0"
    "curIndex\0setCurrentIndex(int)\0"
    "DoRotation()\0UpdateItemCount()\0"
};

void QFlashListAgency::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QFlashListAgency *_t = static_cast<QFlashListAgency *>(_o);
        switch (_id) {
        case 0: _t->sig_setMaximum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sig_setCurrentIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->sig_itemClicked((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2]))); break;
        case 3: _t->setCurrentIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->DoRotation(); break;
        case 5: _t->UpdateItemCount(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QFlashListAgency::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QFlashListAgency::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QFlashListAgency,
      qt_meta_data_QFlashListAgency, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QFlashListAgency::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QFlashListAgency::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QFlashListAgency::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QFlashListAgency))
        return static_cast<void*>(const_cast< QFlashListAgency*>(this));
    return QWidget::qt_metacast(_clname);
}

int QFlashListAgency::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void QFlashListAgency::sig_setMaximum(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QFlashListAgency::sig_setCurrentIndex(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QFlashListAgency::sig_itemClicked(const QString & _t1, long _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
static const uint qt_meta_data_QFlashList[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   12,   11,   11, 0x05,
      58,   47,   11,   11, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_QFlashList[] = {
    "QFlashList\0\0currIndex\0sig_setCurrentIndex(int)\0"
    "str,lData_\0sig_itemClicked(QString,long)\0"
};

void QFlashList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QFlashList *_t = static_cast<QFlashList *>(_o);
        switch (_id) {
        case 0: _t->sig_setCurrentIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sig_itemClicked((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QFlashList::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QFlashList::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QFlashList,
      qt_meta_data_QFlashList, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QFlashList::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QFlashList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QFlashList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QFlashList))
        return static_cast<void*>(const_cast< QFlashList*>(this));
    return QWidget::qt_metacast(_clname);
}

int QFlashList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void QFlashList::sig_setCurrentIndex(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QFlashList::sig_itemClicked(const QString & _t1, long _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
