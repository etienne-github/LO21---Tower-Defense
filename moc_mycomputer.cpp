/****************************************************************************
** Meta object code from reading C++ file 'mycomputer.h'
**
** Created: Sun May 29 23:50:20 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mycomputer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mycomputer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_myComputer[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      25,   11,   11,   11, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_myComputer[] = {
    "myComputer\0\0vieChanged()\0creditChanged()\0"
};

const QMetaObject myComputer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_myComputer,
      qt_meta_data_myComputer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &myComputer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *myComputer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *myComputer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_myComputer))
        return static_cast<void*>(const_cast< myComputer*>(this));
    return QObject::qt_metacast(_clname);
}

int myComputer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: vieChanged(); break;
        case 1: creditChanged(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void myComputer::vieChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void myComputer::creditChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
