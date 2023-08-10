/****************************************************************************
** Meta object code from reading C++ file 'dbus_test_adaptor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.14)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "dbus_test_adaptor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dbus_test_adaptor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.14. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CanDataReceiverAdaptor_t {
    QByteArrayData data[12];
    char stringdata0[531];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CanDataReceiverAdaptor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CanDataReceiverAdaptor_t qt_meta_stringdata_CanDataReceiverAdaptor = {
    {
QT_MOC_LITERAL(0, 0, 22), // "CanDataReceiverAdaptor"
QT_MOC_LITERAL(1, 23, 15), // "D-Bus Interface"
QT_MOC_LITERAL(2, 39, 21), // "local.CanDataReceiver"
QT_MOC_LITERAL(3, 61, 19), // "D-Bus Introspection"
QT_MOC_LITERAL(4, 81, 398), // "  <interface name=\"local.Can..."
QT_MOC_LITERAL(5, 440, 10), // "rpmChanged"
QT_MOC_LITERAL(6, 451, 0), // ""
QT_MOC_LITERAL(7, 452, 6), // "newRpm"
QT_MOC_LITERAL(8, 459, 12), // "speedChanged"
QT_MOC_LITERAL(9, 472, 8), // "newSpeed"
QT_MOC_LITERAL(10, 481, 3), // "rpm"
QT_MOC_LITERAL(11, 485, 5) // "speed"

    },
    "CanDataReceiverAdaptor\0D-Bus Interface\0"
    "local.CanDataReceiver\0D-Bus Introspection\0"
    "  <interface name=\"local.CanDataReceiver\">\n    <property access=\"r"
    "ead\" type=\"d\" name=\"speed\"/>\n    <property access=\"read\" type="
    "\"d\" name=\"rpm\"/>\n    <signal name=\"speedChanged\">\n      <arg d"
    "irection=\"out\" type=\"d\" name=\"newSpeed\"/>\n    </signal>\n    <s"
    "ignal name=\"rpmChanged\">\n      <arg direction=\"out\" type=\"d\" na"
    "me=\"newRpm\"/>\n    </signal>\n  </interface>\n\0"
    "rpmChanged\0\0newRpm\0speedChanged\0"
    "newSpeed\0rpm\0speed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CanDataReceiverAdaptor[] = {

 // content:
       8,       // revision
       0,       // classname
       2,   14, // classinfo
       2,   18, // methods
       2,   34, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // classinfo: key, value
       1,    2,
       3,    4,

 // signals: name, argc, parameters, tag, flags
       5,    1,   28,    6, 0x06 /* Public */,
       8,    1,   31,    6, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Double,    9,

 // properties: name, type, flags
      10, QMetaType::Double, 0x00095001,
      11, QMetaType::Double, 0x00095001,

       0        // eod
};

void CanDataReceiverAdaptor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CanDataReceiverAdaptor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->rpmChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->speedChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CanDataReceiverAdaptor::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CanDataReceiverAdaptor::rpmChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CanDataReceiverAdaptor::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CanDataReceiverAdaptor::speedChanged)) {
                *result = 1;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<CanDataReceiverAdaptor *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< double*>(_v) = _t->rpm(); break;
        case 1: *reinterpret_cast< double*>(_v) = _t->speed(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject CanDataReceiverAdaptor::staticMetaObject = { {
    QMetaObject::SuperData::link<QDBusAbstractAdaptor::staticMetaObject>(),
    qt_meta_stringdata_CanDataReceiverAdaptor.data,
    qt_meta_data_CanDataReceiverAdaptor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CanDataReceiverAdaptor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CanDataReceiverAdaptor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CanDataReceiverAdaptor.stringdata0))
        return static_cast<void*>(this);
    return QDBusAbstractAdaptor::qt_metacast(_clname);
}

int CanDataReceiverAdaptor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractAdaptor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void CanDataReceiverAdaptor::rpmChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CanDataReceiverAdaptor::speedChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
