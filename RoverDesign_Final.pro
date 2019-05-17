#-------------------------------------------------
#
# Project created by QtCreator 2019-05-15T18:46:32
#
#-------------------------------------------------

QT       += core gui

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

greaterThan(QT_MAJOR_VERSION, 4) {
    QT       += widgets serialport
} else {
    include($$QTSERIALPORT_PROJECT_ROOT/src/serialport/qt4support/serialport.prf)
}

TARGET = RoverDesign_Final
TEMPLATE = app

CONFIG += c++11
@CONFIG += serialport@
SOURCES += main.cpp\
        dialog.cpp

HEADERS  += dialog.h

FORMS    +=
