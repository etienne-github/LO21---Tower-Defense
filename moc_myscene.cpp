/****************************************************************************
** Meta object code from reading C++ file 'myscene.h'
**
** Created: Mon May 30 02:54:18 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "myscene.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myscene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_myScene[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      16,    8,    8,    8, 0x0a,
      26,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_myScene[] = {
    "myScene\0\0tick()\0newWave()\0switchTick()\0"
};

const QMetaObject myScene::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_myScene,
      qt_meta_data_myScene, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &myScene::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *myScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *myScene::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_myScene))
        return static_cast<void*>(const_cast< myScene*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int myScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: tick(); break;
        case 1: newWave(); break;
        case 2: switchTick(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void myScene::tick()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
