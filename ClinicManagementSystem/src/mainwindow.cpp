// src/mainwindow.cpp
#include "mainwindow.h"
#include <QApplication>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    dataManager = new DataManager(); // Initialize DataManager
    setupUi();
    setWindowTitle("Clinic Management System - Welcome");

    // Center the window
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);
}

MainWindow::~MainWindow()
{
    delete dataManager;
    // Child widgets are deleted automatically by Qt's parent-child mechanism
}

void MainWindow::setupUi() {
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout(centralWidget);

    titleLabel = new QLabel("Clinic Management System", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    mainLayout->addWidget(titleLabel);

    instructionLabel = new QLabel("Please select your role or register as a new patient.", this);
    instructionLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(instructionLabel);

    mainLayout->addSpacing(20);

    patientButton = new QPushButton("Patient Login / Register", this);
    patientButton->setMinimumHeight(40);
    connect(patientButton, &QPushButton::clicked, this, &MainWindow::openPatientPortal);
    mainLayout->addWidget(patientButton);

    doctorButton = new QPushButton("Doctor Login", this);
    doctorButton->setMinimumHeight(40);
    connect(doctorButton, &QPushButton::clicked, this, &MainWindow::openDoctorPortal);
    mainLayout->addWidget(doctorButton);

    mainLayout->addStretch(); // Pushes widgets to the top

    centralWidget->setLayout(mainLayout);
    resize(400, 250); // Initial size for the main window
}

void MainWindow::openPatientPortal() {
    patientPortalWidget = new PatientPortal(dataManager, this);
    connect(patientPortalWidget, &PatientPortal::backToMainClicked, this, &MainWindow::showMainWindow);
    setCentralWidget(patientPortalWidget);
    patientPortalWidget->show();
    setWindowTitle("Patient Portal");
    resize(600,500); // Resize for patient portal
}

void MainWindow::openDoctorPortal() {
    doctorPortalWidget = new DoctorPortal(dataManager, this);
    connect(doctorPortalWidget, &DoctorPortal::backToMainClicked, this, &MainWindow::showMainWindow);
    setCentralWidget(doctorPortalWidget);
    doctorPortalWidget->show();
    setWindowTitle("Doctor Portal");
    resize(800,600); // Resize for doctor portal
}

void MainWindow::showMainWindow() {
    // Clean up previous portal widget if it exists
    if (patientPortalWidget) {
        patientPortalWidget->deleteLater();
        patientPortalWidget = nullptr;
    }
    if (doctorPortalWidget) {
        doctorPortalWidget->deleteLater();
        doctorPortalWidget = nullptr;
    }

    // Re-setup or simply show the main central widget
    // For simplicity, we recreate the central widget for the main view
    // A more sophisticated approach might involve QStackedWidget
    setupUi(); // This re-creates the main buttons and labels
    setWindowTitle("Clinic Management System - Welcome");
    resize(400, 250); // Reset to initial size
}


