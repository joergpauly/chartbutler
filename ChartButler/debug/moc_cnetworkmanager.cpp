/****************************************************************************
** Meta object code from reading C++ file 'cnetworkmanager.h'
**
** Created: Sat 3. Nov 18:41:29 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../cnetworkmanager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cnetworkmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CNetworkManager[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      35,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      60,   53,   16,   16, 0x0a,
     100,   87,   16,   16, 0x0a,
     126,   16,   16,   16, 0x0a,
     146,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CNetworkManager[] = {
    "CNetworkManager\0\0chartDlFinished()\0"
    "fieldDlFinished()\0pReply\0"
    "dlFinished(QNetworkReply*)\0pRcvd,pTotal\0"
    "dlProgress(qint64,qint64)\0onChartDlFinished()\0"
    "dlNextField()\0"
};

void CNetworkManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CNetworkManager *_t = static_cast<CNetworkManager *>(_o);
        switch (_id) {
        case 0: _t->chartDlFinished(); break;
        case 1: _t->fieldDlFinished(); break;
        case 2: _t->dlFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 3: _t->dlProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 4: _t->onChartDlFinished(); break;
        case 5: _t->dlNextField(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CNetworkManager::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CNetworkManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CNetworkManager,
      qt_meta_data_CNetworkManager, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CNetworkManager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CNetworkManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CNetworkManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CNetworkManager))
        return static_cast<void*>(const_cast< CNetworkManager*>(this));
    return QObject::qt_metacast(_clname);
}

int CNetworkManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void CNetworkManager::chartDlFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void CNetworkManager::fieldDlFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
