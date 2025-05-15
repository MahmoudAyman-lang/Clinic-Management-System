/****************************************************************************
** Meta object code from reading C++ file 'patientportal.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/patientportal.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'patientportal.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN13PatientPortalE_t {};
} // unnamed namespace

template <> constexpr inline auto PatientPortal::qt_create_metaobjectdata<qt_meta_tag_ZN13PatientPortalE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PatientPortal",
        "backToMainClicked",
        "",
        "handlePatientLogin",
        "handlePatientRegister",
        "populateUpcomingAppointments",
        "handleBookAppointment",
        "handleCancelAppointment",
        "handleLogout",
        "onDateSelected",
        "date",
        "onSpecializationSelected",
        "index",
        "onDoctorSelected",
        "updateDoctorComboBox",
        "updateAvailableTimeSlots"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'backToMainClicked'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'handlePatientLogin'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'handlePatientRegister'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'populateUpcomingAppointments'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'handleBookAppointment'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'handleCancelAppointment'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'handleLogout'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onDateSelected'
        QtMocHelpers::SlotData<void(const QDate &)>(9, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QDate, 10 },
        }}),
        // Slot 'onSpecializationSelected'
        QtMocHelpers::SlotData<void(int)>(11, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 12 },
        }}),
        // Slot 'onDoctorSelected'
        QtMocHelpers::SlotData<void(int)>(13, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 12 },
        }}),
        // Slot 'updateDoctorComboBox'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'updateAvailableTimeSlots'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PatientPortal, qt_meta_tag_ZN13PatientPortalE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PatientPortal::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PatientPortalE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PatientPortalE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13PatientPortalE_t>.metaTypes,
    nullptr
} };

void PatientPortal::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PatientPortal *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->backToMainClicked(); break;
        case 1: _t->handlePatientLogin(); break;
        case 2: _t->handlePatientRegister(); break;
        case 3: _t->populateUpcomingAppointments(); break;
        case 4: _t->handleBookAppointment(); break;
        case 5: _t->handleCancelAppointment(); break;
        case 6: _t->handleLogout(); break;
        case 7: _t->onDateSelected((*reinterpret_cast< std::add_pointer_t<QDate>>(_a[1]))); break;
        case 8: _t->onSpecializationSelected((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->onDoctorSelected((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->updateDoctorComboBox(); break;
        case 11: _t->updateAvailableTimeSlots(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (PatientPortal::*)()>(_a, &PatientPortal::backToMainClicked, 0))
            return;
    }
}

const QMetaObject *PatientPortal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PatientPortal::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PatientPortalE_t>.strings))
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
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
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
