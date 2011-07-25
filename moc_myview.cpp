/****************************************************************************
** Meta object code from reading C++ file 'myview.h'
**
** Created: Mon May 30 03:12:01 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "myview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_myView[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,
      23,    7,    7,    7, 0x05,
      43,   39,    7,    7, 0x05,
      68,   39,    7,    7, 0x05,
      92,    7,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
     111,    7,    7,    7, 0x0a,
     127,    7,    7,    7, 0x0a,
     140,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_myView[] = {
    "myView\0\0mouseOnScene()\0mouseOutScene()\0"
    "x,y\0mouseMoving(float,float)\0"
    "mouseClick(float,float)\0mouseDoubleClick()\0"
    "ameliorerItem()\0vendreItem()\0"
    "switchMouseMoving()\0"
};

const QMetaObject myView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_myView,
      qt_meta_data_myView, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &myView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *myView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *myView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_myView))
        return static_cast<void*>(const_cast< myView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int myView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: mouseOnScene(); break;
        case 1: mouseOutScene(); break;
        case 2: mouseMoving((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 3: mouseClick((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 4: mouseDoubleClick(); break;
        case 5: ameliorerItem(); break;
        case 6: vendreItem(); break;
        case 7: switchMouseMoving(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void myView::mouseOnScene()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void myView::mouseOutScene()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void myView::mouseMoving(float _t1, float _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void myView::mouseClick(float _t1, float _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void myView::mouseDoubleClick()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
QT_END_MOC_NAMESPACE
