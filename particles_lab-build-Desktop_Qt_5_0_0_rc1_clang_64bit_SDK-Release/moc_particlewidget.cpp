/****************************************************************************
** Meta object code from reading C++ file 'particlewidget.h'
**
** Created: Fri Dec 7 00:37:31 2012
**      by: The Qt Meta Object Compiler version 67 (Qt 5.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../lab06/src/particlewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'particlewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ParticleWidget_t {
    QByteArrayData data[8];
    char stringdata[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_ParticleWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_ParticleWidget_t qt_meta_stringdata_ParticleWidget = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 7),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 10),
QT_MOC_LITERAL(4, 35, 12),
QT_MOC_LITERAL(5, 48, 14),
QT_MOC_LITERAL(6, 63, 5),
QT_MOC_LITERAL(7, 69, 6)
    },
    "ParticleWidget\0_glInit\0\0_mouseDrag\0"
    "QMouseEvent*\0mouseDragEvent\0event\0"
    "redraw\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ParticleWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x05,
       3,    1,   35,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       5,    1,   38,    2, 0x09,
       7,    0,   41,    2, 0x09,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    6,
    QMetaType::Void,

       0        // eod
};

void ParticleWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ParticleWidget *_t = static_cast<ParticleWidget *>(_o);
        switch (_id) {
        case 0: _t->_glInit(); break;
        case 1: _t->_mouseDrag((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 2: _t->mouseDragEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 3: _t->redraw(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ParticleWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ParticleWidget::_glInit)) {
                *result = 0;
            }
        }
        {
            typedef void (ParticleWidget::*_t)(QMouseEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ParticleWidget::_mouseDrag)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject ParticleWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_ParticleWidget.data,
      qt_meta_data_ParticleWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *ParticleWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ParticleWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ParticleWidget.stringdata))
        return static_cast<void*>(const_cast< ParticleWidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int ParticleWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ParticleWidget::_glInit()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ParticleWidget::_mouseDrag(QMouseEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
