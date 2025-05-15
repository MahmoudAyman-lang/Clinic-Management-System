// src/mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "patientportal.h"
#include "doctorportal.h"
#include "datamanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openPatientPortal();
    void openDoctorPortal();
    void showMainWindow();

private:
    // Ui::MainWindow *ui; // Not using .ui file for this simple example
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QLabel *instructionLabel;
    QPushButton *patientButton;
    QPushButton *doctorButton;

    PatientPortal *patientPortalWidget;
    DoctorPortal *doctorPortalWidget;
    DataManager *dataManager;

    void setupUi();
};
#endif // MAINWINDOW_H

