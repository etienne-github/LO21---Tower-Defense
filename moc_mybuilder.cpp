/****************************************************************************
** Meta object code from reading C++ file 'mybuilder.h'
**
** Created: Mon May 30 03:03:19 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mybuilder.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mybuilder.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_myBuilder[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      31,   10,   10,   10, 0x0a,
      46,   10,   10,   10, 0x0a,
      61,   10,   10,   10, 0x0a,
      81,   77,   10,   10, 0x0a,
     109,  107,   10,   10, 0x0a,
     130,   77,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_myBuilder[] = {
    "myBuilder\0\0switchMouseMoving()\0"
    "disableCuror()\0createCursor()\0"
    "destroyCursor()\0x,y\0updateCursor(float,float)\0"
    "i\0updateActivated(int)\0"
    "createDefense(float,float)\0"
};

const QMetaObject myBuilder::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_myBuilder,
      qt_meta_data_myBuilder, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &myBuilder::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *myBuilder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *myBuilder::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_myBuilder))
        return static_cast<void*>(const_cast< myBuilder*>(this));
    return QObject::qt_metacast(_clname);
}

int myBuilder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: switchMouseMoving(); break;
        case 1: disableCuror(); break;
        case 2: createCursor(); break;
        case 3: destroyCursor(); break;
        case 4: updateCursor((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 5: updateActivated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: createDefense((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void myBuilder::switchMouseMoving()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
