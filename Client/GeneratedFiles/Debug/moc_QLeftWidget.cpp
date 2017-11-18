/****************************************************************************
** Meta object code from reading C++ file 'QLeftWidget.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QLeftWidget.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QLeftWidget.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QLeftWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   13,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      44,   37,   12,   12, 0x0a,
      67,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QLeftWidget[] = {
    "QLeftWidget\0\0,\0sigItem(QString,long)\0"
    "_event\0showEvent(QShowEvent*)\0"
    "onCloseAnima()\0"
};

void QLeftWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QLeftWidget *_t = static_cast<QLeftWidget *>(_o);
        switch (_id) {
        case 0: _t->sigItem((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2]))); break;
        case 1: _t->showEvent((*reinterpret_cast< QShowEvent*(*)>(_a[1]))); break;
        case 2: _t->onCloseAnima(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QLeftWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QLeftWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QLeftWidget,
      qt_meta_data_QLeftWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QLeftWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QLeftWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QLeftWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QLeftWidget))
        return static_cast<void*>(const_cast< QLeftWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QLeftWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void QLeftWidget::sigItem(const QString & _t1, long _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
