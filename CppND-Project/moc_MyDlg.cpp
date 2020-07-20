/****************************************************************************
** Meta object code from reading C++ file 'MyDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MyDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x08,
      28,    6,    6,    6, 0x08,
      55,    6,    6,    6, 0x08,
      80,    6,    6,    6, 0x08,
     102,    6,    6,    6, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MyDlg[] = {
    "MyDlg\0\0onAddButtonClicked()\0"
    "onFirstWordButtonClicked()\0"
    "onSecWordBottonClicked()\0onExitButtonClicked()\0"
    "showTime()\0"
};

void MyDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MyDlg *_t = static_cast<MyDlg *>(_o);
        switch (_id) {
        case 0: _t->onAddButtonClicked(); break;
        case 1: _t->onFirstWordButtonClicked(); break;
        case 2: _t->onSecWordBottonClicked(); break;
        case 3: _t->onExitButtonClicked(); break;
        case 4: _t->showTime(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MyDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MyDlg::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MyDlg,
      qt_meta_data_MyDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyDlg))
        return static_cast<void*>(const_cast< MyDlg*>(this));
    return QWidget::qt_metacast(_clname);
}

int MyDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
