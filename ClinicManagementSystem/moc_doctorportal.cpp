/****************************************************************************
** Meta object code from reading C++ file 'doctorportal.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "src/doctorportal.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'doctorportal.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DoctorPortal_t {
    QByteArrayData data[13];
    char stringdata0[252];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DoctorPortal_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DoctorPortal_t qt_meta_stringdata_DoctorPortal = {
    {
QT_MOC_LITERAL(0, 0, 12), // "DoctorPortal"
QT_MOC_LITERAL(1, 13, 17), // "backToMainClicked"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 17), // "handleDoctorLogin"
QT_MOC_LITERAL(4, 50, 25), // "onDateSelectedForSchedule"
QT_MOC_LITERAL(5, 76, 4), // "date"
QT_MOC_LITERAL(6, 81, 22), // "populateDoctorSchedule"
QT_MOC_LITERAL(7, 104, 24), // "handleViewPatientDetails"
QT_MOC_LITERAL(8, 129, 29), // "handleModifyAppointmentStatus"
QT_MOC_LITERAL(9, 159, 31), // "handleCancelAppointmentByDoctor"
QT_MOC_LITERAL(10, 191, 26), // "handleAddWalkInAppointment"
QT_MOC_LITERAL(11, 218, 20), // "handleGenerateReport"
QT_MOC_LITERAL(12, 239, 12) // "handleLogout"

    },
    "DoctorPortal\0backToMainClicked\0\0"
    "handleDoctorLogin\0onDateSelectedForSchedule\0"
    "date\0populateDoctorSchedule\0"
    "handleViewPatientDetails\0"
    "handleModifyAppointmentStatus\0"
    "handleCancelAppointmentByDoctor\0"
    "handleAddWalkInAppointment\0"
    "handleGenerateReport\0handleLogout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DoctorPortal[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   65,    2, 0x08 /* Private */,
       4,    1,   66,    2, 0x08 /* Private */,
       6,    1,   69,    2, 0x08 /* Private */,
       7,    0,   72,    2, 0x08 /* Private */,
       8,    0,   73,    2, 0x08 /* Private */,
       9,    0,   74,    2, 0x08 /* Private */,
      10,    0,   75,    2, 0x08 /* Private */,
      11,    0,   76,    2, 0x08 /* Private */,
      12,    0,   77,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QDate,    5,
    QMetaType::Void, QMetaType::QDate,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DoctorPortal::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DoctorPortal *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->backToMainClicked(); break;
        case 1: _t->handleDoctorLogin(); break;
        case 2: _t->onDateSelectedForSchedule((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 3: _t->populateDoctorSchedule((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 4: _t->handleViewPatientDetails(); break;
        case 5: _t->handleModifyAppointmentStatus(); break;
        case 6: _t->handleCancelAppointmentByDoctor(); break;
        case 7: _t->handleAddWalkInAppointment(); break;
        case 8: _t->handleGenerateReport(); break;
        case 9: _t->handleLogout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DoctorPortal::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DoctorPortal::backToMainClicked)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DoctorPortal::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_DoctorPortal.data,
    qt_meta_data_DoctorPortal,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DoctorPortal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DoctorPortal::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DoctorPortal.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int DoctorPortal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void DoctorPortal::backToMainClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
