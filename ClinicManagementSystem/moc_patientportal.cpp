/****************************************************************************
** Meta object code from reading C++ file 'patientportal.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "src/patientportal.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'patientportal.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PatientPortal_t {
    QByteArrayData data[16];
    char stringdata0[276];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PatientPortal_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PatientPortal_t qt_meta_stringdata_PatientPortal = {
    {
QT_MOC_LITERAL(0, 0, 13), // "PatientPortal"
QT_MOC_LITERAL(1, 14, 17), // "backToMainClicked"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 18), // "handlePatientLogin"
QT_MOC_LITERAL(4, 52, 21), // "handlePatientRegister"
QT_MOC_LITERAL(5, 74, 28), // "populateUpcomingAppointments"
QT_MOC_LITERAL(6, 103, 21), // "handleBookAppointment"
QT_MOC_LITERAL(7, 125, 23), // "handleCancelAppointment"
QT_MOC_LITERAL(8, 149, 12), // "handleLogout"
QT_MOC_LITERAL(9, 162, 14), // "onDateSelected"
QT_MOC_LITERAL(10, 177, 4), // "date"
QT_MOC_LITERAL(11, 182, 24), // "onSpecializationSelected"
QT_MOC_LITERAL(12, 207, 5), // "index"
QT_MOC_LITERAL(13, 213, 16), // "onDoctorSelected"
QT_MOC_LITERAL(14, 230, 20), // "updateDoctorComboBox"
QT_MOC_LITERAL(15, 251, 24) // "updateAvailableTimeSlots"

    },
    "PatientPortal\0backToMainClicked\0\0"
    "handlePatientLogin\0handlePatientRegister\0"
    "populateUpcomingAppointments\0"
    "handleBookAppointment\0handleCancelAppointment\0"
    "handleLogout\0onDateSelected\0date\0"
    "onSpecializationSelected\0index\0"
    "onDoctorSelected\0updateDoctorComboBox\0"
    "updateAvailableTimeSlots"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PatientPortal[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    1,   81,    2, 0x08 /* Private */,
      11,    1,   84,    2, 0x08 /* Private */,
      13,    1,   87,    2, 0x08 /* Private */,
      14,    0,   90,    2, 0x08 /* Private */,
      15,    0,   91,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QDate,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PatientPortal::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PatientPortal *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->backToMainClicked(); break;
        case 1: _t->handlePatientLogin(); break;
        case 2: _t->handlePatientRegister(); break;
        case 3: _t->populateUpcomingAppointments(); break;
        case 4: _t->handleBookAppointment(); break;
        case 5: _t->handleCancelAppointment(); break;
        case 6: _t->handleLogout(); break;
        case 7: _t->onDateSelected((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 8: _t->onSpecializationSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->onDoctorSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->updateDoctorComboBox(); break;
        case 11: _t->updateAvailableTimeSlots(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PatientPortal::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PatientPortal::backToMainClicked)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PatientPortal::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_PatientPortal.data,
    qt_meta_data_PatientPortal,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PatientPortal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PatientPortal::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PatientPortal.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PatientPortal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void PatientPortal::backToMainClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
