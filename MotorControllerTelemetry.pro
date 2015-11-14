#-------------------------------------------------
#
# Project created by QtCreator 2015-11-14T23:53:10
#
#-------------------------------------------------

CONFIG += c++14
QMAKE_CXXFLAGS_CXX11    = -std=c++1y
QT += core gui

QT += qml quick widgets
QT += serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MotorControllerTelemetry
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Communication/Communication.cpp \
    Communication/CommunicationSerialPort.cpp \
    Communication/CommunicationTcpSocket.cpp \
    Communication/CommunicationTcpSocketServer.cpp \
    Application.cpp

HEADERS  += mainwindow.h \
    Communication/Communication.h \
    Communication/CommunicationSerialPort.h \
    Communication/CommunicationTcpSocket.h \
    Communication/CommunicationTcpSocketServer.h \
    Application.h

FORMS    += mainwindow.ui
