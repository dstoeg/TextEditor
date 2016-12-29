/****************************************************************************
** Meta object code from reading C++ file 'Viewer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Viewer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Viewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Viewer_t {
    QByteArrayData data[11];
    char stringdata0[96];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Viewer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Viewer_t qt_meta_stringdata_Viewer = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Viewer"
QT_MOC_LITERAL(1, 7, 14), // "OnMouseClicked"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 1), // "x"
QT_MOC_LITERAL(4, 25, 1), // "y"
QT_MOC_LITERAL(5, 27, 14), // "OnMouseDragged"
QT_MOC_LITERAL(6, 42, 15), // "OnMouseReleased"
QT_MOC_LITERAL(7, 58, 12), // "OnKeyPressed"
QT_MOC_LITERAL(8, 71, 3), // "key"
QT_MOC_LITERAL(9, 75, 10), // "OnKeyTyped"
QT_MOC_LITERAL(10, 86, 9) // "testToGui"

    },
    "Viewer\0OnMouseClicked\0\0x\0y\0OnMouseDragged\0"
    "OnMouseReleased\0OnKeyPressed\0key\0"
    "OnKeyTyped\0testToGui"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Viewer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x02 /* Public */,
       5,    2,   49,    2, 0x02 /* Public */,
       6,    0,   54,    2, 0x02 /* Public */,
       7,    1,   55,    2, 0x02 /* Public */,
       9,    1,   58,    2, 0x02 /* Public */,
      10,    0,   61,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::QString,

       0        // eod
};

void Viewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Viewer *_t = static_cast<Viewer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnMouseClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->OnMouseDragged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->OnMouseReleased(); break;
        case 3: _t->OnKeyPressed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->OnKeyTyped((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: { QString _r = _t->testToGui();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject Viewer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Viewer.data,
      qt_meta_data_Viewer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Viewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Viewer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Viewer.stringdata0))
        return static_cast<void*>(const_cast< Viewer*>(this));
    if (!strcmp(_clname, "UpdateEventListener"))
        return static_cast< UpdateEventListener*>(const_cast< Viewer*>(this));
    return QObject::qt_metacast(_clname);
}

int Viewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
