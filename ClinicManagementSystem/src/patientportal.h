// src/patientportal.h
#ifndef PATIENTPORTAL_H
#define PATIENTPORTAL_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTabWidget>
#include <QTableWidget>
#include <QCalendarWidget>
#include <QListWidget>
#include <QTextEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QHeaderView>
#include <QCryptographicHash>
#include <QMap>
#include "datamanager.h"

class PatientPortal : public QWidget
{
    Q_OBJECT

public:
    explicit PatientPortal(DataManager *dm, QWidget *parent = nullptr);
    ~PatientPortal();

signals:
    void backToMainClicked();

private slots:
    // Login/Registration Tab Slots
    void handlePatientLogin();
    void handlePatientRegister();

    // Patient Dashboard Slots
    void populateUpcomingAppointments();
    // void populatePastAppointments(); // Optional, if implemented
    void handleBookAppointment();
    // void handleModifyAppointment(); // Simplified for Phase 2
    void handleCancelAppointment();
    void handleLogout();
    void onDateSelected(const QDate &date);
    void onSpecializationSelected(int index);
    void onDoctorSelected(int index);
    void updateDoctorComboBox();
    void updateAvailableTimeSlots(); // Overloaded or modified to use selected doctor

private:
    DataManager *dataManager;
    Patient currentPatient;
    // QString selectedDoctorIdForBooking; // Replaced by doctorComboBox->currentData()

    // Main Layout
    QVBoxLayout *mainLayout;

    // Login/Registration View
    QWidget *loginRegisterWidget;
    QVBoxLayout *loginRegisterLayout;
    QTabWidget *loginRegisterTabs;

    // Login Tab
    QWidget *loginTab;
    QFormLayout *loginFormLayout;
    QLineEdit *loginRegisteredIdEdit; // Changed from loginPatientIdEdit
    QLineEdit *loginPasswordEdit;
    QPushButton *loginButton;
    QLabel *loginStatusLabel;

    // Registration Tab
    QWidget *registrationTab;
    QFormLayout *registrationFormLayout;
    QLineEdit *registerNameEdit;
    QLineEdit *registerPatientIdEdit; // National ID
    QLineEdit *registerPasswordEdit;
    QLineEdit *registerConfirmPasswordEdit;
    QTextEdit *registerMedicalHistoryEdit;
    QPushButton *registerButton;
    QLabel *registrationStatusLabel;

    // Patient Dashboard View
    QWidget *dashboardWidget;
    QVBoxLayout *dashboardLayout;
    QLabel *welcomeLabel;

    QTableWidget *upcomingAppointmentsTable;
    // QPushButton *viewPastAppointmentsButton; // Optional
    // QPushButton *modifyAppointmentButton;
    QPushButton *cancelAppointmentButton;

    QFormLayout *doctorSelectionLayout;
    QComboBox *specializationComboBox;
    QComboBox *doctorComboBox;

    QCalendarWidget *calendarWidget;
    QLabel *availableSlotsLabel;
    QListWidget *timeSlotsListWidget;
    QPushButton *bookAppointmentButton;
    QPushButton *logoutButton;
    QPushButton *backButton; // For login/register screen

    QMap<QString, QString> currentDoctorMap; // Stores Name -> ID for current specialization

    void setupLoginRegisterUI();
    void setupDashboardUI();
    void switchToDashboard();
    void switchToLoginRegister();
    void clearDashboard();
    void clearLoginRegisterFields();
    void populateSpecializations();

    // Helper
    QString hashPassword(const QString& password);
};

#endif // PATIENTPORTAL_H

