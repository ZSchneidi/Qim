/****************************************************************************
** Meta object code from reading C++ file 'coreengine.h'
**
** Created: Fri 6. Aug 14:03:01 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/core/coreengine.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'coreengine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CoreEngine[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      19,   11,   11,   11, 0x08,
      28,   11,   11,   11, 0x08,
      38,   11,   11,   11, 0x08,
      49,   11,   11,   11, 0x08,
      61,   11,   11,   11, 0x08,
      79,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CoreEngine[] = {
    "CoreEngine\0\0open()\0zoomIn()\0zoomOut()\0"
    "showInfo()\0closeInfo()\0navigateForward()\0"
    "navigateBackward()\0"
};

const QMetaObject CoreEngine::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_CoreEngine,
      qt_meta_data_CoreEngine, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CoreEngine::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CoreEngine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CoreEngine::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CoreEngine))
        return static_cast<void*>(const_cast< CoreEngine*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int CoreEngine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: open(); break;
        case 1: zoomIn(); break;
        case 2: zoomOut(); break;
        case 3: showInfo(); break;
        case 4: closeInfo(); break;
        case 5: navigateForward(); break;
        case 6: navigateBackward(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
