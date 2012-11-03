/****************************************************************************
** Meta object code from reading C++ file 'cmainwindow.h'
**
** Created: Sat 3. Nov 18:41:26 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../cmainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cmainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CMainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      35,   12,   12,   12, 0x08,
      55,   12,   12,   12, 0x08,
      79,   12,   12,   12, 0x08,
     114,  102,   12,   12, 0x08,
     167,   12,   12,   12, 0x08,
     182,   12,   12,   12, 0x08,
     195,   12,   12,   12, 0x08,
     210,  102,   12,   12, 0x08,
     274,  257,   12,   12, 0x08,
     341,   12,   12,   12, 0x08,
     366,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CMainWindow[] = {
    "CMainWindow\0\0on_cmdClose_clicked()\0"
    "on_cmdAdd_clicked()\0on_cmdOptions_clicked()\0"
    "on_cmdUpdate_clicked()\0item,column\0"
    "on_trvCharts_itemDoubleClicked(QTreeWidgetItem*,int)\0"
    "on_actRemove()\0on_actShow()\0on_actUpdate()\0"
    "on_trvCharts_itemChanged(QTreeWidgetItem*,int)\0"
    "current,previous\0"
    "on_trvCharts_currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)\0"
    "on_cmdHelpInfo_clicked()\0on_cmdGat24_clicked()\0"
};

void CMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CMainWindow *_t = static_cast<CMainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_cmdClose_clicked(); break;
        case 1: _t->on_cmdAdd_clicked(); break;
        case 2: _t->on_cmdOptions_clicked(); break;
        case 3: _t->on_cmdUpdate_clicked(); break;
        case 4: _t->on_trvCharts_itemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->on_actRemove(); break;
        case 6: _t->on_actShow(); break;
        case 7: _t->on_actUpdate(); break;
        case 8: _t->on_trvCharts_itemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->on_trvCharts_currentItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 10: _t->on_cmdHelpInfo_clicked(); break;
        case 11: _t->on_cmdGat24_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CMainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_CMainWindow,
      qt_meta_data_CMainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CMainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CMainWindow))
        return static_cast<void*>(const_cast< CMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int CMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
