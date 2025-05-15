// src/doctorportal.cpp
#include "doctorportal.h"
#include <QDate>
#include <QTime>
#include <QInputDialog>
#include <QTimer>

DoctorPortal::DoctorPortal(DataManager *dm, QWidget *parent)
    : QWidget(parent), dataManager(dm)
{
    mainLayout = new QVBoxLayout(this);
    setupLoginUI();
    setupDashboardUI();

    mainLayout->addWidget(loginWidget);
    mainLayout->addWidget(dashboardWidget);

    switchToLogin(); // Start with login view
    setLayout(mainLayout);
}

DoctorPortal::~DoctorPortal() {
    // Qt handles deletion of child widgets
}

void DoctorPortal::setupLoginUI() {
    loginWidget = new QWidget(this);
    loginFormLayout = new QFormLayout(loginWidget);

    loginDoctorIdEdit = new QLineEdit();
    loginPasswordEdit = new QLineEdit();
    loginPasswordEdit->setEchoMode(QLineEdit::Password);
    loginButton = new QPushButton("Login");
    loginStatusLabel = new QLabel("");

    loginFormLayout->addRow("Doctor ID (e.g., doc001):", loginDoctorIdEdit);
    loginFormLayout->addRow("Password:", loginPasswordEdit);
    loginFormLayout->addRow(loginButton);
    loginFormLayout->addRow(loginStatusLabel);

    backButtonLogin = new QPushButton("Back to Main Menu");
    loginFormLayout->addRow(backButtonLogin);

    loginWidget->setLayout(loginFormLayout);

    // Connections
    connect(loginButton, &QPushButton::clicked, this, &DoctorPortal::handleDoctorLogin);
    connect(backButtonLogin, &QPushButton::clicked, this, &DoctorPortal::backToMainClicked);
}

void DoctorPortal::setupDashboardUI() {
    dashboardWidget = new QWidget(this);
    dashboardLayout = new QVBoxLayout(dashboardWidget);

    welcomeLabel = new QLabel("Welcome, Dr. [Doctor Name]!");
    QFont welcomeFont = welcomeLabel->font();
    welcomeFont.setPointSize(16);
    welcomeLabel->setFont(welcomeFont);
    dashboardLayout->addWidget(welcomeLabel);

    // Schedule Management
    QLabel *scheduleLabel = new QLabel("Schedule Management:");
    dashboardLayout->addWidget(scheduleLabel);

    QHBoxLayout *scheduleControlsLayout = new QHBoxLayout();
    scheduleCalendarWidget = new QCalendarWidget();
    scheduleCalendarWidget->setMinimumDate(QDate::currentDate().addMonths(-6)); // Allow viewing past few months
    scheduleCalendarWidget->setMaximumDate(QDate::currentDate().addMonths(6));  // And future few months
    scheduleControlsLayout->addWidget(scheduleCalendarWidget);

    QVBoxLayout *appointmentsListLayout = new QVBoxLayout();
    appointmentsForDateLabel = new QLabel("Appointments for [Selected Date]:");
    appointmentsListLayout->addWidget(appointmentsForDateLabel);
    scheduleTableWidget = new QTableWidget();
    scheduleTableWidget->setColumnCount(5);
    scheduleTableWidget->setHorizontalHeaderLabels({"Time", "Patient Name", "Patient ID", "Status", "Notes"});
    scheduleTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    scheduleTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    scheduleTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    scheduleTableWidget->horizontalHeader()->setStretchLastSection(true);
    appointmentsListLayout->addWidget(scheduleTableWidget);
    scheduleControlsLayout->addLayout(appointmentsListLayout);
    dashboardLayout->addLayout(scheduleControlsLayout);

    QHBoxLayout *scheduleActionLayout = new QHBoxLayout();
    viewPatientDetailsButton = new QPushButton("View Patient Details");
    modifyAppointmentStatusButton = new QPushButton("Update Status");
    cancelAppointmentByDoctorButton = new QPushButton("Cancel Appointment");
    addWalkInButton = new QPushButton("Add Walk-in/New");
    scheduleActionLayout->addWidget(viewPatientDetailsButton);
    scheduleActionLayout->addWidget(modifyAppointmentStatusButton);
    scheduleActionLayout->addWidget(cancelAppointmentByDoctorButton);
    scheduleActionLayout->addWidget(addWalkInButton);
    scheduleActionLayout->addStretch();
    dashboardLayout->addLayout(scheduleActionLayout);

    // Reporting
    QLabel *reportingLabel = new QLabel("Generate Reports:");
    dashboardLayout->addWidget(reportingLabel);
    QHBoxLayout *reportingLayout = new QHBoxLayout();
    reportTypeComboBox = new QComboBox();
    reportTypeComboBox->addItems({"Today's Booked Appointments", "Appointments for Selected Date", "Monthly Summary (Selected Month)"});
    reportingLayout->addWidget(reportTypeComboBox);
    generateReportButton = new QPushButton("Generate Text Report");
    reportingLayout->addWidget(generateReportButton);
    reportingLayout->addStretch();
    dashboardLayout->addLayout(reportingLayout);

    logoutButton = new QPushButton("Logout");
    dashboardLayout->addWidget(logoutButton, 0, Qt::AlignRight);

    dashboardWidget->setLayout(dashboardLayout);

    // Connections
    connect(scheduleCalendarWidget, &QCalendarWidget::selectionChanged, this, [this](){
        onDateSelectedForSchedule(scheduleCalendarWidget->selectedDate());
    });
    connect(viewPatientDetailsButton, &QPushButton::clicked, this, &DoctorPortal::handleViewPatientDetails);
    connect(modifyAppointmentStatusButton, &QPushButton::clicked, this, &DoctorPortal::handleModifyAppointmentStatus);
    connect(cancelAppointmentByDoctorButton, &QPushButton::clicked, this, &DoctorPortal::handleCancelAppointmentByDoctor);
    connect(addWalkInButton, &QPushButton::clicked, this, &DoctorPortal::handleAddWalkInAppointment);
    connect(generateReportButton, &QPushButton::clicked, this, &DoctorPortal::handleGenerateReport);
    connect(logoutButton, &QPushButton::clicked, this, &DoctorPortal::handleLogout);

    onDateSelectedForSchedule(QDate::currentDate()); // Populate for today initially
}

QString DoctorPortal::hashPassword(const QString& password) {
    return QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
}

void DoctorPortal::handleDoctorLogin() {
    QString doctorId = loginDoctorIdEdit->text().trimmed();
    QString password = loginPasswordEdit->text();

    if (doctorId.isEmpty() || password.isEmpty()) {
        loginStatusLabel->setText("<font color=\"red\">Doctor ID and Password cannot be empty.</font>");
        return;
    }

    Doctor doctor = dataManager->getDoctorByUsername(doctorId); // Assuming username is systemId
    if (doctor.systemId.isEmpty() || doctor.hashedPassword != hashPassword(password)) {
        loginStatusLabel->setText("<font color=\"red\">Invalid Doctor ID or Password.</font>");
        return;
    }

    currentDoctor = doctor;
    loginStatusLabel->setText("<font color=\"green\">Login successful!</font>");
    QTimer::singleShot(1000, this, &DoctorPortal::switchToDashboard);
}

void DoctorPortal::switchToDashboard() {
    welcomeLabel->setText(QString("Welcome, %1!").arg(currentDoctor.name));
    onDateSelectedForSchedule(QDate::currentDate()); // Refresh schedule
    loginWidget->hide();
    dashboardWidget->show();
    // The MainWindow should handle its own title updates when switching views.
    // emit parentWidget()->parentWidget()->setWindowTitle("Doctor Dashboard - " + currentDoctor.name); // Removed to prevent crash
}

void DoctorPortal::switchToLogin() {
    clearLoginFields();
    clearDashboardFields();
    currentDoctor = Doctor(); // Clear current doctor data
    dashboardWidget->hide();
    loginWidget->show();
    loginStatusLabel->clear();
    // The MainWindow should handle its own title updates when switching views.
    // emit parentWidget()->parentWidget()->setWindowTitle("Doctor Portal - Login"); // Removed to prevent crash
}

void DoctorPortal::clearLoginFields() {
    loginDoctorIdEdit->clear();
    loginPasswordEdit->clear();
    loginStatusLabel->clear();
}

void DoctorPortal::clearDashboardFields() {
    welcomeLabel->setText("Welcome, Dr. [Doctor Name]!");
    scheduleTableWidget->setRowCount(0);
    appointmentsForDateLabel->setText("Appointments for [Selected Date]:");
}

void DoctorPortal::onDateSelectedForSchedule(const QDate &date) {
    appointmentsForDateLabel->setText(QString("Appointments for %1:").arg(date.toString("yyyy-MM-dd")));
    populateDoctorSchedule(date);
}

void DoctorPortal::populateDoctorSchedule(const QDate &date) {
    if (currentDoctor.systemId.isEmpty()) return;

    scheduleTableWidget->setRowCount(0);
    QVector<Appointment> appointments = dataManager->getAppointmentsByDate(date.toString("yyyy-MM-dd"), currentDoctor.systemId);

    for (const auto& app : appointments) {
        // Only show active or recently completed/cancelled appointments for the day
        // if (app.status.toLower() == "cancelled by user" && QDate::fromString(app.date, "yyyy-MM-dd") < QDate::currentDate()) continue;
        // if (app.status.toLower() == "cancelled by clinic" && QDate::fromString(app.date, "yyyy-MM-dd") < QDate::currentDate()) continue;

        int row = scheduleTableWidget->rowCount();
        scheduleTableWidget->insertRow(row);
        scheduleTableWidget->setItem(row, 0, new QTableWidgetItem(app.time));
        Patient p = dataManager->getPatientById(app.patientSystemId);
        scheduleTableWidget->setItem(row, 1, new QTableWidgetItem(p.name.isEmpty() ? "N/A" : p.name));
        scheduleTableWidget->setItem(row, 2, new QTableWidgetItem(app.patientSystemId));
        scheduleTableWidget->setItem(row, 3, new QTableWidgetItem(app.status));
        scheduleTableWidget->setItem(row, 4, new QTableWidgetItem(app.notes));
        // Store appointment ID for later use
        QTableWidgetItem *idItem = new QTableWidgetItem(app.appointmentId);
        scheduleTableWidget->setItem(row, 5, idItem); // Hidden column
    }
    if (scheduleTableWidget->columnCount() > 5) scheduleTableWidget->hideColumn(5); // Hide ID column
    scheduleTableWidget->resizeColumnsToContents();
}

QString DoctorPortal::getSelectedAppointmentIdFromTable(){
    QList<QTableWidgetItem*> selectedItems = scheduleTableWidget->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "Selection Error", "Please select an appointment from the schedule.");
        return QString();
    }
    int selectedRow = scheduleTableWidget->row(selectedItems.first());
    // Assuming appointment ID is in a hidden column 5 (index 5)
    if(scheduleTableWidget->columnCount() > 5 && scheduleTableWidget->item(selectedRow, 5)){
        return scheduleTableWidget->item(selectedRow, 5)->text();
    }
    // Fallback: try to find by other means if ID column isn't there (less reliable)
    QString appTime = scheduleTableWidget->item(selectedRow, 0)->text();
    QString patientId = scheduleTableWidget->item(selectedRow, 2)->text();
    QDate selectedDate = scheduleCalendarWidget->selectedDate();
    QVector<Appointment> appointments = dataManager->getAppointmentsByDate(selectedDate.toString("yyyy-MM-dd"), currentDoctor.systemId);
    for(const auto& app : appointments){
        if(app.time == appTime && app.patientSystemId == patientId){
            return app.appointmentId;
        }
    }
    QMessageBox::critical(this, "Error", "Could not retrieve appointment ID.");
    return QString();
}

void DoctorPortal::handleViewPatientDetails() {
    QString appointmentId = getSelectedAppointmentIdFromTable();
    if (appointmentId.isEmpty()) return;

    Appointment app = dataManager->getAppointmentById(appointmentId);
    if (app.appointmentId.isEmpty()) {
        QMessageBox::critical(this, "Error", "Could not retrieve appointment details.");
        return;
    }
    Patient patient = dataManager->getPatientById(app.patientSystemId);
    if (patient.systemId.isEmpty()) {
        QMessageBox::critical(this, "Error", "Could not retrieve patient details.");
        return;
    }

    QString details = QString("Patient Name: %1\nPatient ID: %2\nRegistered ID: %3\n\nMedical History:\n%4")
                          .arg(patient.name, patient.systemId, patient.registeredIdNumber, patient.medicalHistory);
    QMessageBox::information(this, "Patient Details", details);
}

void DoctorPortal::handleModifyAppointmentStatus() {
    QString appointmentId = getSelectedAppointmentIdFromTable();
    if (appointmentId.isEmpty()) return;

    Appointment app = dataManager->getAppointmentById(appointmentId);
    if (app.appointmentId.isEmpty()) {
        QMessageBox::critical(this, "Error", "Could not retrieve appointment details.");
        return;
    }

    bool ok;
    QStringList statuses = {"Booked", "Confirmed", "Completed", "No Show", "Rescheduled"};
    QString newStatus = QInputDialog::getItem(this, "Update Appointment Status",
                                              "Select new status for appointment on " + app.date + " at " + app.time + ":",
                                              statuses, statuses.indexOf(app.status), false, &ok);

    if (ok && !newStatus.isEmpty() && newStatus != app.status) {
        app.status = newStatus;
        if (dataManager->updateAppointment(app)) {
            QMessageBox::information(this, "Status Updated", "Appointment status updated successfully.");
            populateDoctorSchedule(QDate::fromString(app.date, "yyyy-MM-dd"));
        } else {
            QMessageBox::critical(this, "Update Failed", "Could not update appointment status.");
        }
    }
}

void DoctorPortal::handleCancelAppointmentByDoctor() {
    QString appointmentId = getSelectedAppointmentIdFromTable();
    if (appointmentId.isEmpty()) return;

    Appointment app = dataManager->getAppointmentById(appointmentId);
    if (app.appointmentId.isEmpty()) {
        QMessageBox::critical(this, "Error", "Could not retrieve appointment details.");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Cancellation",
                                  QString("Are you sure you want to cancel the appointment for patient %1 on %2 at %3?")
                                  .arg(dataManager->getPatientById(app.patientSystemId).name, app.date, app.time),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        app.status = "Cancelled by clinic";
        bool ok;
        QString reason = QInputDialog::getText(this, "Cancellation Reason", "Reason for cancellation (optional):", QLineEdit::Normal, "", &ok);
        if(ok) app.notes = reason;

        if (dataManager->updateAppointment(app)) {
            QMessageBox::information(this, "Appointment Cancelled", "The appointment has been cancelled.");
            populateDoctorSchedule(QDate::fromString(app.date, "yyyy-MM-dd"));
        } else {
            QMessageBox::critical(this, "Cancellation Failed", "Could not cancel the appointment.");
        }
    }
}

void DoctorPortal::handleAddWalkInAppointment() {
    if (currentDoctor.systemId.isEmpty()) {
        QMessageBox::warning(this, "Error", "Doctor not logged in.");
        return;
    }

    QDate selectedDate = scheduleCalendarWidget->selectedDate();
    bool ok;
    QString patientName = QInputDialog::getText(this, "Add Walk-in Appointment", "Patient Name:", QLineEdit::Normal, "", &ok);
    if (!ok || patientName.isEmpty()) return;

    QString patientRegisteredId = QInputDialog::getText(this, "Add Walk-in Appointment", "Patient Registered ID (if known, else leave blank for new/temp):", QLineEdit::Normal, "", &ok);
    // if (!ok) return; // Allow blank

    QString timeSlot = QInputDialog::getText(this, "Add Walk-in Appointment", QString("Time (HH:mm) for %1:").arg(selectedDate.toString("yyyy-MM-dd")), QLineEdit::Normal, "", &ok);
    if (!ok || timeSlot.isEmpty() || !QTime::fromString(timeSlot, "HH:mm").isValid()) {
        QMessageBox::warning(this, "Invalid Time", "Please enter a valid time in HH:mm format.");
        return;
    }

    // Check if patient exists or create a temporary one
    Patient patient = dataManager->getPatientByRegisteredId(patientRegisteredId);
    QString patientSystemIdToUse;
    if(patient.systemId.isEmpty() && !patientRegisteredId.isEmpty()){
        // If ID provided but not found, maybe ask to register first or create temp
        QMessageBox::StandardButton regReply = QMessageBox::question(this, "Patient Not Found",
                                                                   QString("Patient with Registered ID ") + patientRegisteredId + " not found. Create a temporary record for this appointment?",
                                                                   QMessageBox::Yes|QMessageBox::No);
        if(regReply == QMessageBox::No) return;
        // Create a temporary patient record (or a simplified one for walk-in)
        Patient tempPatient;
        tempPatient.systemId = dataManager->generateNewPatientId(); // Needs a unique system ID
        tempPatient.registeredIdNumber = patientRegisteredId.isEmpty() ? "WALKIN-" + tempPatient.systemId : patientRegisteredId;
        tempPatient.name = patientName;
        tempPatient.hashedPassword = ""; // No login for temp walk-in
        tempPatient.medicalHistory = "Walk-in appointment.";
        if(!dataManager->addPatient(tempPatient)){
            QMessageBox::critical(this, "Error", "Could not create temporary patient record.");
            return;
        }
        patientSystemIdToUse = tempPatient.systemId;
    } else if (!patient.systemId.isEmpty()) {
        patientSystemIdToUse = patient.systemId;
    } else { // No registered ID provided, create temp patient
        Patient tempPatient;
        tempPatient.systemId = dataManager->generateNewPatientId();
        tempPatient.registeredIdNumber = "WALKIN-" + tempPatient.systemId;
        tempPatient.name = patientName;
        tempPatient.hashedPassword = "";
        tempPatient.medicalHistory = "Walk-in appointment.";
        if(!dataManager->addPatient(tempPatient)){
            QMessageBox::critical(this, "Error", "Could not create temporary patient record for walk-in.");
            return;
        }
        patientSystemIdToUse = tempPatient.systemId;
    }

    Appointment newAppointment;
    newAppointment.appointmentId = dataManager->generateNewAppointmentId();
    newAppointment.patientSystemId = patientSystemIdToUse;
    newAppointment.doctorSystemId = currentDoctor.systemId;
    newAppointment.date = selectedDate.toString("yyyy-MM-dd");
    newAppointment.time = timeSlot;
    newAppointment.status = "Booked (Walk-in)";
    newAppointment.notes = "Added by doctor as walk-in.";

    if (dataManager->addAppointment(newAppointment)) {
        QMessageBox::information(this, "Appointment Added", "Walk-in appointment added successfully.");
        populateDoctorSchedule(selectedDate);
    } else {
        QMessageBox::critical(this, "Add Failed", "Could not add walk-in appointment. The slot might be taken or another error occurred.");
    }
}

void DoctorPortal::handleGenerateReport() {
    if (currentDoctor.systemId.isEmpty()) {
        QMessageBox::warning(this, "Error", "Doctor not logged in.");
        return;
    }

    QString reportType = reportTypeComboBox->currentText();
    QString reportContent = "Report Type: " + reportType + "\nGenerated for: Dr. " + currentDoctor.name + " (ID: " + currentDoctor.systemId + ")\nDate Generated: " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") + "\n\n";
    QDate selectedDateForReport = scheduleCalendarWidget->selectedDate();

    QVector<Appointment> appointmentsToReport;

    if (reportType == "Today's Booked Appointments") {
        appointmentsToReport = dataManager->getAppointmentsByDate(QDate::currentDate().toString("yyyy-MM-dd"), currentDoctor.systemId);
        reportContent += "Appointments for Today (" + QDate::currentDate().toString("yyyy-MM-dd") + "):\n";
    } else if (reportType == "Appointments for Selected Date") {
        appointmentsToReport = dataManager->getAppointmentsByDate(selectedDateForReport.toString("yyyy-MM-dd"), currentDoctor.systemId);
        reportContent += "Appointments for " + selectedDateForReport.toString("yyyy-MM-dd") + ":\n";
    } else if (reportType == "Monthly Summary (Selected Month)") {
        QVector<Appointment> allDoctorAppointments = dataManager->getAppointmentsByDoctorId(currentDoctor.systemId);
        reportContent += "Summary for " + selectedDateForReport.toString("MMMM yyyy") + ":\n";
        int count = 0;
        for(const auto& app : allDoctorAppointments){
            QDate appDate = QDate::fromString(app.date, "yyyy-MM-dd");
            if(appDate.year() == selectedDateForReport.year() && appDate.month() == selectedDateForReport.month()){
                appointmentsToReport.append(app);
                count++;
            }
        }
        reportContent += QString("Total appointments in %1: %2\n").arg(selectedDateForReport.toString("MMMM yyyy")).arg(count);
    }

    if (appointmentsToReport.isEmpty() && !(reportType == "Monthly Summary (Selected Month)" && !reportContent.contains("Total appointments"))) {
        reportContent += "No appointments found for this selection.\n";
    } else {
        for (const auto& app : appointmentsToReport) {
            Patient p = dataManager->getPatientById(app.patientSystemId);
            reportContent += QString("- Time: %1, Patient: %2 (ID: %3), Status: %4, Notes: %5\n")
                               .arg(app.time, p.name.isEmpty() ? "N/A" : p.name, app.patientSystemId, app.status, app.notes);
        }
    }

    // For simplicity, show report in a QMessageBox. For real app, save to file or print.
    QMessageBox reportBox;
    reportBox.setWindowTitle("Generated Report");
    reportBox.setTextFormat(Qt::PlainText);
    reportBox.setText(reportContent);
    reportBox.setStandardButtons(QMessageBox::Ok);
    reportBox.exec();
}

void DoctorPortal::handleLogout() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Logout", "Are you sure you want to logout?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        switchToLogin();
        emit backToMainClicked(); // Signal MainWindow to show main selection screen
    }
}
