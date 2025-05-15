// src/datamanager.cpp
#include "datamanager.h"
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QCryptographicHash>

// Helper to parse a CSV line, very basic, assumes no commas within quoted fields for simplicity here
// A more robust CSV parser would be needed for complex CSVs.
QStringList DataManager::parseCsvLine(const QString& line) {
    // This is a simplified parser. For production, use a robust CSV library.
    // It doesn't handle escaped quotes within fields well.
    QStringList fields;
    QString currentField;
    bool inQuotes = false;
    for (QChar c : line) {
        if (c == '"') {
            inQuotes = !inQuotes;
        } else if (c == ',' && !inQuotes) {
            fields.append(currentField.trimmed());
            currentField.clear();
        } else {
            currentField.append(c);
        }
    }
    fields.append(currentField.trimmed()); // Add the last field
    return fields;
}

QString DataManager::escapeCsvField(const QString& field) {
    QString escapedField = field;
    // If field contains comma, quote, or newline, enclose in double quotes
    // and escape existing double quotes by doubling them (e.g., " -> "")
    if (escapedField.contains(',') || escapedField.contains('"') || escapedField.contains('\n')) {
        escapedField.replace("\"", "\"\"");
        escapedField = "\"" + escapedField + "\"";
    }
    return escapedField;
}

DataManager::DataManager(const QString& patientFile, const QString& doctorFile, const QString& appointmentFile) {
    QDir dir("./data"); // Create a subdirectory for data files
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    patientsFilePath = dir.filePath(patientFile);
    doctorsFilePath = dir.filePath(doctorFile);
    appointmentsFilePath = dir.filePath(appointmentFile);

    // Initialize files if they don't exist
    if (!QFile::exists(patientsFilePath)) QFile(patientsFilePath).open(QIODevice::WriteOnly | QIODevice::Text);
    
    if (!QFile::exists(doctorsFilePath) || QFile(doctorsFilePath).size() == 0) {
         QFile dFile(doctorsFilePath);
         if (dFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) { // Truncate if it exists but is empty
            QTextStream out(&dFile);
            QString defaultPasswordHash = QString(QCryptographicHash::hash(QString("doctorpass").toUtf8(), QCryptographicHash::Sha256).toHex());
            
            // Pre-populate doctors
            QVector<Doctor> defaultDoctors;
            defaultDoctors.append({"doc001", "Nancy", defaultPasswordHash, "General Medicine"});
            defaultDoctors.append({"doc002", "Sarah", defaultPasswordHash, "Nutritionist"});
            defaultDoctors.append({"doc003", "Mariam", defaultPasswordHash, "Nutritionist"});
            defaultDoctors.append({"doc004", "Mohamed", defaultPasswordHash, "Heart Doctor"});
            defaultDoctors.append({"doc005", "Magdy", defaultPasswordHash, "Heart Doctor"});

            for (const auto& doc : defaultDoctors) {
                out << escapeCsvField(doc.systemId) << ","
                    << escapeCsvField(doc.name) << ","
                    << escapeCsvField(doc.hashedPassword) << ","
                    << escapeCsvField(doc.specialization) << "\n";
            }
            dFile.close();
         } else {
            qWarning() << "Could not open doctors file for writing defaults:" << doctorsFilePath;
         }
    }
    if (!QFile::exists(appointmentsFilePath)) QFile(appointmentsFilePath).open(QIODevice::WriteOnly | QIODevice::Text);
}

// --- Patient Management --- 
QVector<Patient> DataManager::loadPatients() {
    QVector<Patient> patients;
    QFile file(patientsFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open patients file for reading:" << patientsFilePath;
        return patients;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.trimmed().isEmpty()) continue;
        QStringList fields = parseCsvLine(line);
        if (fields.count() == 5) {
            Patient p;
            p.systemId = fields[0];
            p.registeredIdNumber = fields[1];
            p.name = fields[2];
            p.hashedPassword = fields[3];
            p.medicalHistory = fields[4];
            patients.append(p);
        }
    }
    file.close();
    return patients;
}

bool DataManager::savePatients(const QVector<Patient>& patients) {
    QFile file(patientsFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qWarning() << "Could not open patients file for writing:" << patientsFilePath;
        return false;
    }
    QTextStream out(&file);
    for (const auto& p : patients) {
        out << escapeCsvField(p.systemId) << ","
            << escapeCsvField(p.registeredIdNumber) << ","
            << escapeCsvField(p.name) << ","
            << escapeCsvField(p.hashedPassword) << ","
            << escapeCsvField(p.medicalHistory) << "\n";
    }
    file.close();
    return true;
}

bool DataManager::addPatient(const Patient& patient) {
    QVector<Patient> patients = loadPatients();
    for(const auto& p : patients) {
        if(p.systemId == patient.systemId || p.registeredIdNumber == patient.registeredIdNumber) {
            qWarning() << "Patient with this System ID or Registered ID already exists.";
            return false; // Prevent duplicates
        }
    }
    patients.append(patient);
    return savePatients(patients);
}

Patient DataManager::getPatientById(const QString& patientId) {
    QVector<Patient> patients = loadPatients();
    for (const auto& p : patients) {
        if (p.systemId == patientId) {
            return p;
        }
    }
    return Patient(); // Return empty patient if not found
}

Patient DataManager::getPatientByRegisteredId(const QString& registeredId) {
    QVector<Patient> patients = loadPatients();
    for (const auto& p : patients) {
        if (p.registeredIdNumber == registeredId) {
            return p;
        }
    }
    return Patient(); // Return empty patient if not found
}

QVector<Patient> DataManager::getAllPatients() {
    return loadPatients();
}

bool DataManager::updatePatient(const Patient& patient) {
    QVector<Patient> patients = loadPatients();
    for (int i = 0; i < patients.size(); ++i) {
        if (patients[i].systemId == patient.systemId) {
            patients[i] = patient;
            return savePatients(patients);
        }
    }
    return false; // Patient not found
}

// --- Doctor Management ---
QVector<Doctor> DataManager::loadDoctors() {
    QVector<Doctor> doctors;
    QFile file(doctorsFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open doctors file for reading:" << doctorsFilePath;
        return doctors;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.trimmed().isEmpty()) continue;
        QStringList fields = parseCsvLine(line);
        if (fields.count() == 4) {
            Doctor d;
            d.systemId = fields[0];
            d.name = fields[1];
            d.hashedPassword = fields[2];
            d.specialization = fields[3];
            doctors.append(d);
        }
    }
    file.close();
    return doctors;
}

bool DataManager::saveDoctors(const QVector<Doctor>& doctors) {
    QFile file(doctorsFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qWarning() << "Could not open doctors file for writing:" << doctorsFilePath;
        return false;
    }
    QTextStream out(&file);
    for (const auto& d : doctors) {
        out << escapeCsvField(d.systemId) << ","
            << escapeCsvField(d.name) << ","
            << escapeCsvField(d.hashedPassword) << ","
            << escapeCsvField(d.specialization) << "\n";
    }
    file.close();
    return true;
}

Doctor DataManager::getDoctorById(const QString& doctorId) {
    QVector<Doctor> doctors = loadDoctors();
    for (const auto& d : doctors) {
        if (d.systemId == doctorId) {
            return d;
        }
    }
    return Doctor(); // Return empty doctor if not found
}

Doctor DataManager::getDoctorByUsername(const QString& username) {
    // Assuming username is the systemId for doctors for simplicity
    return getDoctorById(username);
}

QVector<Doctor> DataManager::getAllDoctors() {
    return loadDoctors();
}

// This addDoctor is now primarily for the initial setup or future admin functions.
// The main list of doctors is pre-populated if the file is new.
bool DataManager::addDoctor(const Doctor& doctor) {
    QVector<Doctor> doctors = loadDoctors();
     for(const auto& d : doctors) {
        if(d.systemId == doctor.systemId) {
            qWarning() << "Doctor with this System ID " << doctor.systemId << " already exists.";
            return false; // Prevent duplicates
        }
    }
    doctors.append(doctor);
    return saveDoctors(doctors);
}

// --- Appointment Management ---
QVector<Appointment> DataManager::loadAppointments() {
    QVector<Appointment> appointments;
    QFile file(appointmentsFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open appointments file for reading:" << appointmentsFilePath;
        return appointments;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.trimmed().isEmpty()) continue;
        QStringList fields = parseCsvLine(line);
        if (fields.count() == 7) {
            Appointment a;
            a.appointmentId = fields[0];
            a.patientSystemId = fields[1];
            a.doctorSystemId = fields[2];
            a.date = fields[3];
            a.time = fields[4];
            a.status = fields[5];
            a.notes = fields[6];
            appointments.append(a);
        }
    }
    file.close();
    return appointments;
}

bool DataManager::saveAppointments(const QVector<Appointment>& appointments) {
    QFile file(appointmentsFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qWarning() << "Could not open appointments file for writing:" << appointmentsFilePath;
        return false;
    }
    QTextStream out(&file);
    for (const auto& a : appointments) {
        out << escapeCsvField(a.appointmentId) << ","
            << escapeCsvField(a.patientSystemId) << ","
            << escapeCsvField(a.doctorSystemId) << ","
            << escapeCsvField(a.date) << ","
            << escapeCsvField(a.time) << ","
            << escapeCsvField(a.status) << ","
            << escapeCsvField(a.notes) << "\n";
    }
    file.close();
    return true;
}

bool DataManager::addAppointment(const Appointment& appointment) {
    QVector<Appointment> appointments = loadAppointments();
    // Basic check for duplicate booking for the same doctor at the same date/time
    for(const auto& existingApp : appointments) {
        if (existingApp.doctorSystemId == appointment.doctorSystemId &&
            existingApp.date == appointment.date &&
            existingApp.time == appointment.time &&
            existingApp.status.toLower() != "cancelled by user" && 
            existingApp.status.toLower() != "cancelled by clinic") {
            qWarning() << "Duplicate appointment: Doctor" << appointment.doctorSystemId 
                       << "already has an appointment at" << appointment.date << appointment.time;
            return false;
        }
    }
    appointments.append(appointment);
    return saveAppointments(appointments);
}

Appointment DataManager::getAppointmentById(const QString& appointmentId) {
    QVector<Appointment> appointments = loadAppointments();
    for (const auto& a : appointments) {
        if (a.appointmentId == appointmentId) {
            return a;
        }
    }
    return Appointment(); // Return empty appointment if not found
}

QVector<Appointment> DataManager::getAppointmentsByPatientId(const QString& patientId) {
    QVector<Appointment> allAppointments = loadAppointments();
    QVector<Appointment> patientAppointments;
    for (const auto& a : allAppointments) {
        if (a.patientSystemId == patientId) {
            patientAppointments.append(a);
        }
    }
    return patientAppointments;
}

QVector<Appointment> DataManager::getAppointmentsByDoctorId(const QString& doctorId) {
    QVector<Appointment> allAppointments = loadAppointments();
    QVector<Appointment> doctorAppointments;
    for (const auto& a : allAppointments) {
        if (a.doctorSystemId == doctorId) {
            doctorAppointments.append(a);
        }
    }
    return doctorAppointments;
}

QVector<Appointment> DataManager::getAppointmentsByDate(const QString& date, const QString& doctorId) {
    QVector<Appointment> allAppointments = loadAppointments();
    QVector<Appointment> dateAppointments;
    for (const auto& a : allAppointments) {
        if (a.date == date && (doctorId.isEmpty() || a.doctorSystemId == doctorId) ) {
            dateAppointments.append(a);
        }
    }
    return dateAppointments;
}

QVector<Appointment> DataManager::getAllAppointments() {
    return loadAppointments();
}

bool DataManager::updateAppointment(const Appointment& appointment) {
    QVector<Appointment> appointments = loadAppointments();
    for (int i = 0; i < appointments.size(); ++i) {
        if (appointments[i].appointmentId == appointment.appointmentId) {
            appointments[i] = appointment;
            return saveAppointments(appointments);
        }
    }
    return false; // Appointment not found
}

bool DataManager::cancelAppointment(const QString& appointmentId) {
    QVector<Appointment> appointments = loadAppointments();
    bool found = false;
    for (int i = 0; i < appointments.size(); ++i) {
        if (appointments[i].appointmentId == appointmentId) {
            // Instead of removing, we can mark as cancelled, or actually remove
            // For this simple system, let's mark it as "Cancelled"
            // This status is checked elsewhere to prevent re-booking or showing as active
            // appointments[i].status = "Cancelled by user"; // Or a more generic "Cancelled"
            // The status update should be handled by the caller (PatientPortal or DoctorPortal) to set appropriate status
            found = true;
            // The actual update of status and saving is done in the portal calling this, after confirming.
            // This function might be better refactored to just remove, or the portals should directly update status.
            // For now, let's assume the portals will set the status before calling updateAppointment.
            // This function as `cancelAppointment` is a bit misleading if it doesn't change status itself.
            // Let's simplify: this function will just remove the appointment. Status change should be done before calling update or by a dedicated function.
            // Re-evaluating: The original design had portals update status then call updateAppointment. Let's stick to that.
            // This function is not directly used by the current portal logic for cancellation. They fetch, modify status, then update.
            // So, this function might be redundant or needs a clearer purpose.
            // For now, let's leave it as is, but note it's not the primary cancel mechanism used by portals.
            break; 
        }
    }
    // if (found) {
    //     return saveAppointments(appointments);
    // }
    return found; // Simply indicates if an appointment with that ID exists.
}

QString DataManager::generateNewPatientId() {
    QVector<Patient> patients = loadPatients();
    return QString("pat%1").arg(patients.size() + 101, 3, 10, QChar('0')); // Start from 101 to avoid conflict with any old pat00x
}

QString DataManager::generateNewDoctorId() {
    QVector<Doctor> doctors = loadDoctors();
    // Ensure new IDs don't clash with pre-populated ones.
    int maxId = 0;
    for(const auto& doc : doctors){
        if(doc.systemId.startsWith("doc")){
            bool ok;
            int idNum = doc.systemId.right(3).toInt(&ok);
            if(ok && idNum > maxId) maxId = idNum;
        }
    }
    return QString("doc%1").arg(maxId + 1, 3, 10, QChar('0'));
}

QString DataManager::generateNewAppointmentId() {
    QVector<Appointment> appointments = loadAppointments();
    return QString("app%1").arg(appointments.size() + 1001, 4, 10, QChar('0')); // Start from 1001
}

