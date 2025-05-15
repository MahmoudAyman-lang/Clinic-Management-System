// src/doctorportal.h
#ifndef DOCTORPORTAL_H
#define DOCTORPORTAL_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QCalendarWidget>
#include <QComboBox>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QHeaderView>
#include <QCryptographicHash>
#include "datamanager.h"

class DoctorPortal : public QWidget
{
    Q_OBJECT

public:
    explicit DoctorPortal(DataManager *dm, QWidget *parent = nullptr);
    ~DoctorPortal();

signals:
    void backToMainClicked();

private slots:
    // Login Slots
    void handleDoctorLogin();

    // Dashboard Slots
    void onDateSelectedForSchedule(const QDate &date);
    void populateDoctorSchedule(const QDate &date);
    void handleViewPatientDetails();
    void handleModifyAppointmentStatus(); // Simplified: just change status
    void handleCancelAppointmentByDoctor();
    void handleAddWalkInAppointment(); // Simplified version
    void handleGenerateReport();
    void handleLogout();

private:
    DataManager *dataManager;
    Doctor currentDoctor;

    // Main Layout
    QVBoxLayout *mainLayout;

    // Login View
    QWidget *loginWidget;
    QFormLayout *loginFormLayout;
    QLineEdit *loginDoctorIdEdit;
    QLineEdit *loginPasswordEdit;
    QPushButton *loginButton;
    QLabel *loginStatusLabel;
    QPushButton *backButtonLogin;

    // Doctor Dashboard View
    QWidget *dashboardWidget;
    QVBoxLayout *dashboardLayout;
    QLabel *welcomeLabel;

    // Schedule Management
    QCalendarWidget *scheduleCalendarWidget;
    QLabel *appointmentsForDateLabel;
    QTableWidget *scheduleTableWidget;
    QPushButton *viewPatientDetailsButton;
    QPushButton *modifyAppointmentStatusButton;
    QPushButton *cancelAppointmentByDoctorButton;
    QPushButton *addWalkInButton;

    // Reporting
    QComboBox *reportTypeComboBox;
    QPushButton *generateReportButton;

    QPushButton *logoutButton;

    void setupLoginUI();
    void setupDashboardUI();
    void switchToDashboard();
    void switchToLogin();
    void clearDashboardFields();
    void clearLoginFields();

    // Helper
    QString hashPassword(const QString& password);
    QString getSelectedAppointmentIdFromTable();

};

#endif // DOCTORPORTAL_H

