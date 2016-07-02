/****************************************************************************
** Meta object code from reading C++ file 'signdetectorapp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../signdetectorapp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'signdetectorapp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SignDetectorApp_t {
    QByteArrayData data[8];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SignDetectorApp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SignDetectorApp_t qt_meta_stringdata_SignDetectorApp = {
    {
QT_MOC_LITERAL(0, 0, 15), // "SignDetectorApp"
QT_MOC_LITERAL(1, 16, 3), // "run"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 10), // "finishExec"
QT_MOC_LITERAL(4, 32, 15), // "ChangeROIMethod"
QT_MOC_LITERAL(5, 48, 1), // "i"
QT_MOC_LITERAL(6, 50, 13), // "newClassifier"
QT_MOC_LITERAL(7, 64, 16) // "changeDataSetDir"

    },
    "SignDetectorApp\0run\0\0finishExec\0"
    "ChangeROIMethod\0i\0newClassifier\0"
    "changeDataSetDir"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SignDetectorApp[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    0,   40,    2, 0x0a /* Public */,
       4,    1,   41,    2, 0x0a /* Public */,
       6,    0,   44,    2, 0x0a /* Public */,
       7,    0,   45,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SignDetectorApp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SignDetectorApp *_t = static_cast<SignDetectorApp *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->run(); break;
        case 1: _t->finishExec(); break;
        case 2: _t->ChangeROIMethod((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->newClassifier(); break;
        case 4: _t->changeDataSetDir(); break;
        default: ;
        }
    }
}

const QMetaObject SignDetectorApp::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_SignDetectorApp.data,
      qt_meta_data_SignDetectorApp,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SignDetectorApp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SignDetectorApp::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SignDetectorApp.stringdata0))
        return static_cast<void*>(const_cast< SignDetectorApp*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int SignDetectorApp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
