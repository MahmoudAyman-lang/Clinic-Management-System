QT += core gui widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated prior to Qt 5.12.0._WARNINGS_AND_DISABLE_TRACE
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x050C00

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/patientportal.cpp \
    src/doctorportal.cpp \
    src/datamanager.cpp

HEADERS += \
    src/mainwindow.h \
    src/patientportal.h \
    src/doctorportal.h \
    src/datamanager.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

