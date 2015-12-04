#-------------------------------------------------
#
# Project created by QtCreator 2015-11-14T23:53:10
#
#-------------------------------------------------

CONFIG += c++14
CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
QMAKE_CXXFLAGS_CXX11    = -std=c++1y
QT += core gui
QT += qml quick widgets
QT += serialport
QT += printsupport

TARGET = MotorControllerTelemetry
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Communication/Communication.cpp \
    Communication/CommunicationSerialPort.cpp \
    Communication/CommunicationTcpSocket.cpp \
    Communication/CommunicationTcpSocketServer.cpp \
    Application.cpp \
    Communication/CommunicationTcpSocketClient.cpp \
    DataParser.cpp \
    customplotitem.cpp \
    qcustomplot.cpp \
    windowseventhandler.cpp


RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)


HEADERS  += mainwindow.h \
    Communication/Communication.h \
    Communication/CommunicationSerialPort.h \
    Communication/CommunicationTcpSocket.h \
    Communication/CommunicationTcpSocketServer.h \
    Application.h \
    Communication/CommunicationTcpSocketClient.h \
    DataParser.h \
    customplotitem.h \
    qcustomplot.h \
    windowseventhandler.h

FORMS    += mainwindow.ui
