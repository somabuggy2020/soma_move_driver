#-------------------------------------------------
#
# Project created by QtCreator 2020-10-13T19:06:38
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = soma_move_driver
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += /usr/local/include/EposCmdLib
LIBS += -L/usr/local/lib/EposCmdLib -lEposCmd

LIBS += -ludev

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/main.cpp \
        src/mainwindow.cpp \
        src/Data/data.cpp \
        src/Xbox/xbox.cpp \
        src/Xbox/Gamepad/gamepad.c \
        src/Hardware/Motor/motor.cpp \
        src/Hardware/hardware.cpp \
        src/Hardware/hardwareinfoviewer.cpp \
        src/Hardware/Clutch/clutch.cpp \
        src/Hardware/Rotary/rotary.cpp \
        src/Behavior/behavior.cpp \
        src/Behavior/statebase.cpp \
        src/Behavior/States/stop.cpp \
        src/Behavior/States/starting.cpp \
        src/Behavior/States/traveling.cpp \
        src/Behavior/States/stopping.cpp \
    src/Behavior/States/manualcontrol.cpp \
    src/Hardware/hardwaremanualcontrolpanel.cpp

HEADERS += \
        src/mainwindow.h \
        src/Data/data.h \
        src/Common/configfilepath.h \
        src/Common/definitions.h \
        src/Xbox/xbox.h \
        src/Xbox/Gamepad/gamepad.h \
        src/Hardware/Motor/motor.h \
        src/Hardware/Motor/motorinfo.h \
        src/Hardware/hardware.h \
        src/Hardware/hardwareinfo.h \
        src/Hardware/hardwareinfoviewer.h \
        src/Hardware/Clutch/clutch.h \
        src/Hardware/Clutch/clutchinfo.h \
        src/Hardware/Rotary/rotary.h \
        src/Hardware/Rotary/rotaryinfo.h \
        src/Behavior/behavior.h \
        src/Behavior/statebase.h \
        src/Behavior/States/stop.h \
        src/Behavior/States/starting.h \
        src/Behavior/States/traveling.h \
        src/Behavior/States/stopping.h \
    src/Behavior/States/manualcontrol.h \
    src/Hardware/hardwaremanualcontrolpanel.h

FORMS += \
        src/mainwindow.ui \
    src/Hardware/hardwareinfoviewer.ui \
    src/Hardware/hardwaremanualcontrolpanel.ui

RESOURCES += \
    resource/resource.qrc

