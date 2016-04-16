/****************************************************************************
** Meta object code from reading C++ file 'options.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../options.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'options.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_optionFunctions_t {
    QByteArrayData data[5];
    char stringdata0[46];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_optionFunctions_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_optionFunctions_t qt_meta_stringdata_optionFunctions = {
    {
QT_MOC_LITERAL(0, 0, 15), // "optionFunctions"
QT_MOC_LITERAL(1, 16, 7), // "exitApp"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 11), // "restartGame"
QT_MOC_LITERAL(4, 37, 8) // "saveGame"

    },
    "optionFunctions\0exitApp\0\0restartGame\0"
    "saveGame"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_optionFunctions[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void optionFunctions::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        optionFunctions *_t = static_cast<optionFunctions *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->exitApp(); break;
        case 1: _t->restartGame(); break;
        case 2: _t->saveGame(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject optionFunctions::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_optionFunctions.data,
      qt_meta_data_optionFunctions,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *optionFunctions::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *optionFunctions::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_optionFunctions.stringdata0))
        return static_cast<void*>(const_cast< optionFunctions*>(this));
    return QWidget::qt_metacast(_clname);
}

int optionFunctions::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
struct qt_meta_stringdata_saveDialog_t {
    QByteArrayData data[6];
    char stringdata0[57];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_saveDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_saveDialog_t qt_meta_stringdata_saveDialog = {
    {
QT_MOC_LITERAL(0, 0, 10), // "saveDialog"
QT_MOC_LITERAL(1, 11, 10), // "createFile"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 15), // "recordInputText"
QT_MOC_LITERAL(4, 39, 5), // "input"
QT_MOC_LITERAL(5, 45, 11) // "closeDialog"

    },
    "saveDialog\0createFile\0\0recordInputText\0"
    "input\0closeDialog"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_saveDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    1,   30,    2, 0x0a /* Public */,
       5,    0,   33,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,

       0        // eod
};

void saveDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        saveDialog *_t = static_cast<saveDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->createFile(); break;
        case 1: _t->recordInputText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->closeDialog(); break;
        default: ;
        }
    }
}

const QMetaObject saveDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_saveDialog.data,
      qt_meta_data_saveDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *saveDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *saveDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_saveDialog.stringdata0))
        return static_cast<void*>(const_cast< saveDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int saveDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
