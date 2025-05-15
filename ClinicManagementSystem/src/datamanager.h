// src/datamanager.h
#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QDebug>

struct Patient {
    QString systemId;
    QString registeredIdNumber;
    QString name;
    QString hashedPassword;
    QString medicalHistory;
};

struct Doctor {
    QString systemId;
    QString name;
    QString hashedPassword;
    QString specialization;
};

struct Appointment {
    QString appointmentId;
    QString patientSystemId;
    QString doctorSystemId;
    QString date;
    QString time;
    QString status;
    QString notes;
};

class DataManager {
public:
    DataManager(const QString& patientFile = "patients.txt",
                const QString& doctorFile = "doctors.txt",
                const QString& appointmentFile = "appointments.txt");

    // Patient Management
    bool addPatient(const Patient& patient);
    Patient getPatientById(const QString& patientId);
    Patient getPatientByRegisteredId(const QString& registeredId);
    QVector<Patient> getAllPatients();
    bool updatePatient(const Patient& patient);

    // Doctor Management (primarily for login and associating with appointments)
    Doctor getDoctorById(const QString& doctorId);
    Doctor getDoctorByUsername(const QString& username); // Assuming username is systemId for simplicity
    QVector<Doctor> getAllDoctors();
    bool addDoctor(const Doctor& doctor); // For initial setup or admin functions

    // Appointment Management
    bool addAppointment(const Appointment& appointment);
    Appointment getAppointmentById(const QString& appointmentId);
    QVector<Appointment> getAppointmentsByPatientId(const QString& patientId);
    QVector<Appointment> getAppointmentsByDoctorId(const QString& doctorId);
    QVector<Appointment> getAppointmentsByDate(const QString& date, const QString& doctorId = "");
    QVector<Appointment> getAllAppointments();
    bool updateAppointment(const Appointment& appointment);
    bool cancelAppointment(const QString& appointmentId);
    QString generateNewPatientId();
    QString generateNewDoctorId();
    QString generateNewAppointmentId();

private:
    QString patientsFilePath;
    QString doctorsFilePath;
    QString appointmentsFilePath;

    QVector<Patient> loadPatients();
    bool savePatients(const QVector<Patient>& patients);

    QVector<Doctor> loadDoctors();
    bool saveDoctors(const QVector<Doctor>& doctors);

    QVector<Appointment> loadAppointments();
    bool saveAppointments(const QVector<Appointment>& appointments);

    // Helper to read a line and split by comma, handling quoted fields if necessary
    QStringList parseCsvLine(const QString& line);
    QString escapeCsvField(const QString& field);
};

#endif // DATAMANAGER_H

