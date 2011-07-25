/****************************************************************************
** Meta object code from reading C++ file 'insecte.h'
**
** Created: Mon May 30 02:47:27 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "insecte.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'insecte.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Insecte[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      23,    8,    8,    8, 0x0a,
      35,    8,    8,    8, 0x0a,
      49,    8,    8,    8, 0x0a,
      73,    8,    8,    8, 0x0a,
      98,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Insecte[] = {
    "Insecte\0\0changeFrame()\0slotPoser()\0"
    "slotEnvoler()\0slotVitesseBackNormal()\0"
    "VitesseBackNormalPaint()\0slotFils2()\0"
};

const QMetaObject Insecte::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Insecte,
      qt_meta_data_Insecte, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Insecte::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Insecte::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Insecte::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Insecte))
        return static_cast<void*>(const_cast< Insecte*>(this));
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< Insecte*>(this));
    return QObject::qt_metacast(_clname);
}

int Insecte::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: changeFrame(); break;
        case 1: slotPoser(); break;
        case 2: slotEnvoler(); break;
        case 3: slotVitesseBackNormal(); break;
        case 4: VitesseBackNormalPaint(); break;
        case 5: slotFils2(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
