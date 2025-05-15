// src/patientportal.cpp
#include "patientportal.h"
#include <QDate>
#include <QTime>
#include <QTimer>
#include <QSet>

PatientPortal::PatientPortal(DataManager *dm, QWidget *parent)
    : QWidget(parent), dataManager(dm)
{
    mainLayout = new QVBoxLayout(this);
    setupLoginRegisterUI();
    setupDashboardUI(); // Setup both, but only one will be visible at a time

    mainLayout->addWidget(loginRegisterWidget);
    mainLayout->addWidget(dashboardWidget);

    switchToLoginRegister(); // Start with login/register view
    setLayout(mainLayout);
    if (parentWidget() && parentWidget()->parentWidget()) {
        parentWidget()->parentWidget()->setWindowTitle("Patient Portal - Login/Register");
    }
}

PatientPortal::~PatientPortal() {
    // Qt handles deletion of child widgets
}

void PatientPortal::setupLoginRegisterUI() {
    loginRegisterWidget = new QWidget(this);
    loginRegisterLayout = new QVBoxLayout(loginRegisterWidget);

    loginRegisterTabs = new QTabWidget(loginRegisterWidget);

    // Login Tab
    loginTab = new QWidget();
    loginFormLayout = new QFormLayout(loginTab);
    loginRegisteredIdEdit = new QLineEdit(); // Changed from loginPatientIdEdit
    loginRegisteredIdEdit->setPlaceholderText("Enter your Registered ID (e.g., National ID)"); // Changed placeholder
    loginPasswordEdit = new QLineEdit();
    loginPasswordEdit->setEchoMode(QLineEdit::Password);
    loginPasswordEdit->setPlaceholderText("Enter your password");
    loginButton = new QPushButton("Login");
    loginStatusLabel = new QLabel("");
    loginFormLayout->addRow("Registered ID Number:", loginRegisteredIdEdit); // Changed label
    loginFormLayout->addRow("Password:", loginPasswordEdit);
    loginFormLayout->addRow(loginButton);
    loginFormLayout->addRow(loginStatusLabel);
    loginTab->setLayout(loginFormLayout);
    loginRegisterTabs->addTab(loginTab, "Login");

    // Registration Tab
    registrationTab = new QWidget();
    registrationFormLayout = new QFormLayout(registrationTab);
    registerNameEdit = new QLineEdit();
    registerPatientIdEdit = new QLineEdit(); // This is the Registered ID Number
    registerPatientIdEdit->setPlaceholderText("e.g., National ID, Passport No.");
    registerPasswordEdit = new QLineEdit();
    registerPasswordEdit->setEchoMode(QLineEdit::Password);
    registerPasswordEdit->setPlaceholderText("Min. 8 characters");
    registerConfirmPasswordEdit = new QLineEdit();
    registerConfirmPasswordEdit->setEchoMode(QLineEdit::Password);
    registerMedicalHistoryEdit = new QTextEdit();
    registerMedicalHistoryEdit->setPlaceholderText("Brief medical history (optional)");
    registerButton = new QPushButton("Register");
    registrationStatusLabel = new QLabel("");

    registrationFormLayout->addRow("Full Name:", registerNameEdit);
    registrationFormLayout->addRow("Registered ID Number:", registerPatientIdEdit);
    registrationFormLayout->addRow("Password:", registerPasswordEdit);
    registrationFormLayout->addRow("Confirm Password:", registerConfirmPasswordEdit);
    registrationFormLayout->addRow("Medical History:", registerMedicalHistoryEdit);
    registrationFormLayout->addRow(registerButton);
    registrationFormLayout->addRow(registrationStatusLabel);
    registrationTab->setLayout(registrationFormLayout);
    loginRegisterTabs->addTab(registrationTab, "Register");

    loginRegisterLayout->addWidget(loginRegisterTabs);

    backButton = new QPushButton("Back to Main Menu");
    loginRegisterLayout->addWidget(backButton, 0, Qt::AlignRight);

    loginRegisterWidget->setLayout(loginRegisterLayout);

    // Connections
    connect(loginButton, &QPushButton::clicked, this, &PatientPortal::handlePatientLogin);
    connect(registerButton, &QPushButton::clicked, this, &PatientPortal::handlePatientRegister);
    connect(backButton, &QPushButton::clicked, this, &PatientPortal::backToMainClicked);
}

void PatientPortal::setupDashboardUI() {
    dashboardWidget = new QWidget(this);
    dashboardLayout = new QVBoxLayout(dashboardWidget);

    welcomeLabel = new QLabel("Welcome, [Patient Name]!");
    QFont welcomeFont = welcomeLabel->font();
    welcomeFont.setPointSize(16);
    welcomeLabel->setFont(welcomeFont);
    dashboardLayout->addWidget(welcomeLabel);

    // Upcoming Appointments
    QLabel *upcomingAppointmentsLabel = new QLabel("My Upcoming Appointments:");
    dashboardLayout->addWidget(upcomingAppointmentsLabel);
    upcomingAppointmentsTable = new QTableWidget();
    upcomingAppointmentsTable->setColumnCount(5); // Date, Time, Doctor, Specialization, Status
    upcomingAppointmentsTable->setHorizontalHeaderLabels({"Date", "Time", "Doctor", "Specialization", "Status"});
    upcomingAppointmentsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    upcomingAppointmentsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    upcomingAppointmentsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    upcomingAppointmentsTable->horizontalHeader()->setStretchLastSection(true);
    upcomingAppointmentsTable->verticalHeader()->setVisible(false);
    dashboardLayout->addWidget(upcomingAppointmentsTable);

    QHBoxLayout *appointmentActionLayout = new QHBoxLayout();
    cancelAppointmentButton = new QPushButton("Cancel Selected Appointment");
    appointmentActionLayout->addWidget(cancelAppointmentButton);
    appointmentActionLayout->addStretch();
    dashboardLayout->addLayout(appointmentActionLayout);

    // Book New Appointment
    QLabel *bookAppointmentLabel = new QLabel("Book a New Appointment:");
    QFont bookFont = bookAppointmentLabel->font();
    bookFont.setPointSize(12);
    bookAppointmentLabel->setFont(bookFont);
    dashboardLayout->addWidget(bookAppointmentLabel);

    doctorSelectionLayout = new QFormLayout();
    specializationComboBox = new QComboBox();
    doctorComboBox = new QComboBox();
    doctorSelectionLayout->addRow("Select Specialization:", specializationComboBox);
    doctorSelectionLayout->addRow("Select Doctor:", doctorComboBox);
    dashboardLayout->addLayout(doctorSelectionLayout);

    QHBoxLayout *bookingLayout = new QHBoxLayout();
    calendarWidget = new QCalendarWidget();
    calendarWidget->setMinimumDate(QDate::currentDate());
    calendarWidget->setEnabled(false); // Disabled until a doctor is selected
    bookingLayout->addWidget(calendarWidget);

    QVBoxLayout *slotsLayout = new QVBoxLayout();
    availableSlotsLabel = new QLabel("Available Time Slots:");
    slotsLayout->addWidget(availableSlotsLabel);
    timeSlotsListWidget = new QListWidget();
    slotsLayout->addWidget(timeSlotsListWidget);
    bookAppointmentButton = new QPushButton("Book Selected Slot");
    bookAppointmentButton->setEnabled(false); // Disabled until doctor and slot selected
    slotsLayout->addWidget(bookAppointmentButton);
    bookingLayout->addLayout(slotsLayout);
    dashboardLayout->addLayout(bookingLayout);

    logoutButton = new QPushButton("Logout");
    dashboardLayout->addWidget(logoutButton, 0, Qt::AlignRight);

    dashboardWidget->setLayout(dashboardLayout);

    // Connections
    connect(specializationComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &PatientPortal::onSpecializationSelected);
    connect(doctorComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &PatientPortal::onDoctorSelected);
    connect(calendarWidget, &QCalendarWidget::selectionChanged, this, [this](){ onDateSelected(calendarWidget->selectedDate()); });
    connect(timeSlotsListWidget, &QListWidget::currentItemChanged, this, [this](QListWidgetItem *current, QListWidgetItem *previous){
        Q_UNUSED(previous);
        bookAppointmentButton->setEnabled(current != nullptr && !current->text().startsWith("No available slots"));
    });
    connect(bookAppointmentButton, &QPushButton::clicked, this, &PatientPortal::handleBookAppointment);
    connect(cancelAppointmentButton, &QPushButton::clicked, this, &PatientPortal::handleCancelAppointment);
    connect(logoutButton, &QPushButton::clicked, this, &PatientPortal::handleLogout);

    populateSpecializations();
}

QString PatientPortal::hashPassword(const QString& password) {
    return QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
}

void PatientPortal::handlePatientLogin() {
    QString registeredId = loginRegisteredIdEdit->text().trimmed(); // Changed from loginPatientIdEdit
    QString password = loginPasswordEdit->text();

    if (registeredId.isEmpty() || password.isEmpty()) {
        loginStatusLabel->setText("<font color=\"red\">Registered ID and Password cannot be empty.</font>"); // Changed message
        return;
    }

    Patient patient = dataManager->getPatientByRegisteredId(registeredId); // Changed to use Registered ID
    if (patient.systemId.isEmpty() || patient.hashedPassword != hashPassword(password)) { // systemId check is still valid to see if patient was found
        loginStatusLabel->setText("<font color=\"red\">Invalid Registered ID or Password.</font>"); // Changed message
        return;
    }

    currentPatient = patient;
    loginStatusLabel->setText("<font color=\"green\">Login successful!</font>");
    QTimer::singleShot(1000, this, &PatientPortal::switchToDashboard);
}

void PatientPortal::handlePatientRegister() {
    QString name = registerNameEdit->text().trimmed();
    QString registeredId = registerPatientIdEdit->text().trimmed(); // This is the Registered ID Number
    QString password = registerPasswordEdit->text();
    QString confirmPassword = registerConfirmPasswordEdit->text();
    QString medicalHistory = registerMedicalHistoryEdit->toPlainText().trimmed();

    if (name.isEmpty() || registeredId.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
        registrationStatusLabel->setText("<font color=\"red\">Full Name, Registered ID, and Password fields are required.</font>");
        return;
    }
    if (password != confirmPassword) {
        registrationStatusLabel->setText("<font color=\"red\">Passwords do not match.</font>");
        return;
    }
    if (password.length() < 8) {
        registrationStatusLabel->setText("<font color=\"red\">Password must be at least 8 characters.</font>");
        return;
    }

    if (!dataManager->getPatientByRegisteredId(registeredId).systemId.isEmpty()) {
        registrationStatusLabel->setText("<font color=\"red\">A patient with this Registered ID already exists.</font>");
        return;
    }

    Patient newPatient;
    newPatient.systemId = dataManager->generateNewPatientId(); // System ID is still generated internally
    newPatient.name = name;
    newPatient.registeredIdNumber = registeredId;
    newPatient.hashedPassword = hashPassword(password);
    newPatient.medicalHistory = medicalHistory;

    if (dataManager->addPatient(newPatient)) {
        registrationStatusLabel->setText("<font color=\"green\">Registration successful! You can now log in using your Registered ID Number.</font>"); // Updated message
        clearLoginRegisterFields();
        loginRegisterTabs->setCurrentIndex(0);
    } else {
        registrationStatusLabel->setText("<font color=\"red\">Registration failed. A user with this system ID might already exist or another error occurred.</font>");
    }
}

void PatientPortal::switchToDashboard() {
    welcomeLabel->setText(QString("Welcome, %1!").arg(currentPatient.name));
    populateUpcomingAppointments();
    populateSpecializations(); 
    loginRegisterWidget->hide();
    dashboardWidget->show();
    if (parentWidget() && parentWidget()->parentWidget()) {
        parentWidget()->parentWidget()->setWindowTitle("Patient Dashboard - " + currentPatient.name);
    }
}

void PatientPortal::switchToLoginRegister() {
    clearLoginRegisterFields();
    clearDashboard();
    currentPatient = Patient();
    dashboardWidget->hide();
    loginRegisterWidget->show();
    loginRegisterTabs->setCurrentIndex(0);
    loginStatusLabel->clear();
    registrationStatusLabel->clear();
    if (parentWidget() && parentWidget()->parentWidget()) {
         parentWidget()->parentWidget()->setWindowTitle("Patient Portal - Login/Register");
    }
}

void PatientPortal::clearLoginRegisterFields() {
    loginRegisteredIdEdit->clear(); // Changed from loginPatientIdEdit
    loginPasswordEdit->clear();
    loginStatusLabel->clear();
    registerNameEdit->clear();
    registerPatientIdEdit->clear();
    registerPasswordEdit->clear();
    registerConfirmPasswordEdit->clear();
    registerMedicalHistoryEdit->clear();
    registrationStatusLabel->clear();
}

void PatientPortal::clearDashboard() {
    welcomeLabel->setText("Welcome, [Patient Name]!");
    upcomingAppointmentsTable->setRowCount(0);
    specializationComboBox->clear();
    doctorComboBox->clear();
    timeSlotsListWidget->clear();
    availableSlotsLabel->setText("Available Time Slots:");
    calendarWidget->setEnabled(false);
    bookAppointmentButton->setEnabled(false);
}

void PatientPortal::populateSpecializations() {
    specializationComboBox->blockSignals(true);
    specializationComboBox->clear();
    QVector<Doctor> allDoctors = dataManager->getAllDoctors();
    QSet<QString> specializations;
    for (const auto& doc : allDoctors) {
        specializations.insert(doc.specialization);
    }
    specializationComboBox->addItem("-- Select Specialization --", QVariant(""));
    for (const QString& spec : qAsConst(specializations)) {
        specializationComboBox->addItem(spec, spec);
    }
    specializationComboBox->blockSignals(false);
    
    if (specializations.isEmpty()) {
        doctorComboBox->setEnabled(false);
        calendarWidget->setEnabled(false);
        bookAppointmentButton->setEnabled(false);
    } else {
        // Do not enable doctorComboBox here, it's handled by onSpecializationSelected
    }
    onSpecializationSelected(0); // Trigger update for doctors based on default selection
}

void PatientPortal::onSpecializationSelected(int index) {
    Q_UNUSED(index);
    updateDoctorComboBox();
}

void PatientPortal::updateDoctorComboBox() {
    doctorComboBox->blockSignals(true);
    doctorComboBox->clear();
    currentDoctorMap.clear();
    QString selectedSpecialization = specializationComboBox->currentData().toString();

    doctorComboBox->addItem("-- Select Doctor --", QVariant(""));
    if (selectedSpecialization.isEmpty()) {
        doctorComboBox->setEnabled(false);
        calendarWidget->setEnabled(false);
        bookAppointmentButton->setEnabled(false);
    } else {
        doctorComboBox->setEnabled(true);
        QVector<Doctor> allDoctors = dataManager->getAllDoctors();
        for (const auto& doc : allDoctors) {
            if (doc.specialization == selectedSpecialization) {
                doctorComboBox->addItem(doc.name, doc.systemId);
                currentDoctorMap[doc.name] = doc.systemId;
            }
        }
        if (doctorComboBox->count() <= 1) { // Only "-- Select Doctor --"
            doctorComboBox->setEnabled(false);
            calendarWidget->setEnabled(false);
            bookAppointmentButton->setEnabled(false);
        }
    }
    doctorComboBox->blockSignals(false);
    onDoctorSelected(0); // Trigger update for calendar/slots based on default doctor selection
}

void PatientPortal::onDoctorSelected(int index) {
    Q_UNUSED(index);
    QString selectedDoctorId = doctorComboBox->currentData().toString();
    if (selectedDoctorId.isEmpty()) {
        calendarWidget->setEnabled(false);
        bookAppointmentButton->setEnabled(false);
    } else {
        calendarWidget->setEnabled(true);
    }
    updateAvailableTimeSlots();
}

void PatientPortal::onDateSelected(const QDate &date) {
    Q_UNUSED(date);
    updateAvailableTimeSlots();
}

void PatientPortal::updateAvailableTimeSlots() {
    timeSlotsListWidget->clear();
    bookAppointmentButton->setEnabled(false);
    QString selectedDoctorId = doctorComboBox->currentData().toString();
    QDate selectedDate = calendarWidget->selectedDate();

    if (selectedDoctorId.isEmpty()) {
        availableSlotsLabel->setText("Please select a doctor to see available slots.");
        return;
    }

    Doctor selectedDoc = dataManager->getDoctorById(selectedDoctorId);
    availableSlotsLabel->setText(QString("Available Slots for Dr. %1 on %2:").arg(selectedDoc.name).arg(selectedDate.toString("yyyy-MM-dd")));

    QVector<QString> allSlots = {"09:00", "09:30", "10:00", "10:30", "11:00", "11:30",
                                 "14:00", "14:30", "15:00", "15:30", "16:00", "16:30"};

    QVector<Appointment> existingAppointments = dataManager->getAppointmentsByDate(selectedDate.toString("yyyy-MM-dd"), selectedDoctorId);
    QSet<QString> bookedSlots;
    for(const auto& app : existingAppointments) {
        if (app.status.toLower() != "cancelled by user" && app.status.toLower() != "cancelled by clinic") {
            bookedSlots.insert(app.time);
        }
    }

    for (const QString& slot : allSlots) {
        if (!bookedSlots.contains(slot)) {
            if (selectedDate == QDate::currentDate() && QTime::fromString(slot, "HH:mm") <= QTime::currentTime().addSecs(60*5)) { // 5 min buffer
                continue;
            }
            timeSlotsListWidget->addItem(slot);
        }
    }
    if(timeSlotsListWidget->count() == 0){
        timeSlotsListWidget->addItem("No available slots for this day/doctor.");
    }
}

void PatientPortal::populateUpcomingAppointments() {
    if (currentPatient.systemId.isEmpty()) return;

    upcomingAppointmentsTable->setRowCount(0);
    QVector<Appointment> appointments = dataManager->getAppointmentsByPatientId(currentPatient.systemId);
    QDate today = QDate::currentDate();

    for (const auto& app : appointments) {
        QDate appDate = QDate::fromString(app.date, "yyyy-MM-dd");
        if (appDate >= today && app.status.toLower() != "cancelled by user" && app.status.toLower() != "cancelled by clinic" && app.status.toLower() != "completed") {
            int row = upcomingAppointmentsTable->rowCount();
            upcomingAppointmentsTable->insertRow(row);
            upcomingAppointmentsTable->setItem(row, 0, new QTableWidgetItem(app.date));
            upcomingAppointmentsTable->setItem(row, 1, new QTableWidgetItem(app.time));
            Doctor doc = dataManager->getDoctorById(app.doctorSystemId);
            upcomingAppointmentsTable->setItem(row, 2, new QTableWidgetItem(doc.name.isEmpty() ? app.doctorSystemId : doc.name));
            upcomingAppointmentsTable->setItem(row, 3, new QTableWidgetItem(doc.specialization));
            upcomingAppointmentsTable->setItem(row, 4, new QTableWidgetItem(app.status));
            upcomingAppointmentsTable->item(row, 0)->setData(Qt::UserRole, app.appointmentId);
        }
    }
}

void PatientPortal::handleBookAppointment() {
    if (currentPatient.systemId.isEmpty()) {
        QMessageBox::warning(this, "Booking Error", "You must be logged in to book an appointment.");
        return;
    }
    QString selectedDoctorId = doctorComboBox->currentData().toString();
    if (selectedDoctorId.isEmpty()) {
        QMessageBox::warning(this, "Booking Error", "Please select a doctor.");
        return;
    }

    QListWidgetItem *selectedSlotItem = timeSlotsListWidget->currentItem();
    if (!selectedSlotItem || selectedSlotItem->text().startsWith("No available slots")) {
        QMessageBox::warning(this, "Booking Error", "Please select an available time slot.");
        return;
    }

    QDate selectedDate = calendarWidget->selectedDate();
    QString selectedTime = selectedSlotItem->text();

    Appointment newAppointment;
    newAppointment.appointmentId = dataManager->generateNewAppointmentId();
    newAppointment.patientSystemId = currentPatient.systemId;
    newAppointment.doctorSystemId = selectedDoctorId;
    newAppointment.date = selectedDate.toString("yyyy-MM-dd");
    newAppointment.time = selectedTime;
    newAppointment.status = "Booked";
    newAppointment.notes = "Booked by patient.";

    if (dataManager->addAppointment(newAppointment)) {
        QMessageBox::information(this, "Booking Successful", QString("Appointment booked with Dr. %1 on %2 at %3.").arg(doctorComboBox->currentText()).arg(newAppointment.date, newAppointment.time));
        populateUpcomingAppointments();
        updateAvailableTimeSlots();
    } else {
        QMessageBox::critical(this, "Booking Failed", "Could not book appointment. The slot might have just been taken or a system error occurred.");
    }
}

void PatientPortal::handleCancelAppointment() {
    QList<QTableWidgetItem*> selectedItems = upcomingAppointmentsTable->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "Cancellation Error", "Please select an appointment from the table to cancel.");
        return;
    }

    int selectedRow = selectedItems.first()->row();
    QString appointmentId = upcomingAppointmentsTable->item(selectedRow, 0)->data(Qt::UserRole).toString();

    if (appointmentId.isEmpty()) {
        QMessageBox::critical(this, "Error", "Could not retrieve appointment ID for cancellation.");
        return;
    }

    Appointment appDetails = dataManager->getAppointmentById(appointmentId);
    if(appDetails.appointmentId.isEmpty()){
        QMessageBox::critical(this, "Error", "Appointment details not found for cancellation.");
        return;
    }
    Doctor doctorDetails = dataManager->getDoctorById(appDetails.doctorSystemId);

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Cancellation", 
                                  QString("Are you sure you want to cancel your appointment with Dr. %1 (%2) on %3 at %4?")
                                  .arg(doctorDetails.name)
                                  .arg(doctorDetails.specialization)
                                  .arg(appDetails.date)
                                  .arg(appDetails.time),
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        Appointment appToCancel = appDetails;
        appToCancel.status = "Cancelled by User";
        if (dataManager->updateAppointment(appToCancel)) {
            QMessageBox::information(this, "Cancellation Successful", "Appointment cancelled.");
            populateUpcomingAppointments();
            updateAvailableTimeSlots(); 
        } else {
            QMessageBox::critical(this, "Cancellation Failed", "Could not update appointment status.");
        }
    }
}

void PatientPortal::handleLogout() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Logout", "Are you sure you want to logout?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        switchToLoginRegister();
        emit backToMainClicked(); 
    }
}

