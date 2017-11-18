/****************************************************************************
** Meta object code from reading C++ file 'MainFrame.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MainFrame.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainFrame.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainFrame[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      26,   10,   10,   10, 0x0a,
      42,   10,   10,   10, 0x0a,
      58,   56,   10,   10, 0x0a,
      86,   10,   10,   10, 0x0a,
     100,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainFrame[] = {
    "MainFrame\0\0onMaxMinized()\0onMove(QPoint&)\0"
    "onShowLight()\0,\0onItemClicked(QString,long)\0"
    "onShowRight()\0onSetWindowTle(QString)\0"
};

void MainFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainFrame *_t = static_cast<MainFrame *>(_o);
        switch (_id) {
        case 0: _t->onMaxMinized(); break;
        case 1: _t->onMove((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 2: _t->onShowLight(); break;
        case 3: _t->onItemClicked((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2]))); break;
        case 4: _t->onShowRight(); break;
        case 5: _t->onSetWindowTle((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainFrame::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainFrame::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainFrame,
      qt_meta_data_MainFrame, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainFrame::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainFrame))
        return static_cast<void*>(const_cast< MainFrame*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
