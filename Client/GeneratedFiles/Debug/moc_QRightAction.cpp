/****************************************************************************
** Meta object code from reading C++ file 'QRightAction.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QRightAction.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QRightAction.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QRightAction[] = {

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
      14,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      27,   13,   13,   13, 0x0a,
      44,   42,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QRightAction[] = {
    "QRightAction\0\0sigMinSize()\0onCloseAnima()\0"
    ",\0onItemClicked(QString,long)\0"
};

void QRightAction::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QRightAction *_t = static_cast<QRightAction *>(_o);
        switch (_id) {
        case 0: _t->sigMinSize(); break;
        case 1: _t->onCloseAnima(); break;
        case 2: _t->onItemClicked((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QRightAction::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QRightAction::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QRightAction,
      qt_meta_data_QRightAction, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QRightAction::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QRightAction::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QRightAction::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QRightAction))
        return static_cast<void*>(const_cast< QRightAction*>(this));
    return QWidget::qt_metacast(_clname);
}

int QRightAction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void QRightAction::sigMinSize()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE