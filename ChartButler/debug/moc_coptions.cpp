/****************************************************************************
** Meta object code from reading C++ file 'coptions.h'
**
** Created: Sat 3. Nov 17:53:54 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../coptions.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'coptions.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_COptions[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      37,    9,    9,    9, 0x08,
      61,    9,    9,    9, 0x08,
      85,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_COptions[] = {
    "COptions\0\0on_cmdBrowsePath_clicked()\0"
    "on_buttonBox_accepted()\0on_buttonBox_rejected()\0"
    "on_cmdBrowsePdf_clicked()\0"
};

void COptions::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        COptions *_t = static_cast<COptions *>(_o);
        switch (_id) {
        case 0: _t->on_cmdBrowsePath_clicked(); break;
        case 1: _t->on_buttonBox_accepted(); break;
        case 2: _t->on_buttonBox_rejected(); break;
        case 3: _t->on_cmdBrowsePdf_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData COptions::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject COptions::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_COptions,
      qt_meta_data_COptions, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &COptions::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *COptions::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *COptions::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_COptions))
        return static_cast<void*>(const_cast< COptions*>(this));
    return QDialog::qt_metacast(_clname);
}

int COptions::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
