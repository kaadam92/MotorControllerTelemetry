#pragma once
#ifndef STVAPPLICATION_H
#define STVAPPLICATION_H
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QString>
#include <QVector>
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QMap>
#include "DataParser.h"
#include "mainwindow.h"
#include "Communication/CommunicationTcpSocketServer.h"
#include "Communication/CommunicationTcpSocketClient.h"
#include "Communication/CommunicationSerialPort.h"
#include "windowseventhandler.h"
#include "qcustomplot.h"
#include "customplotitem.h"



/**
 * @brief Alkalmazás osztály. A main() példányosítja és indítja el.
 *
 * A konstruktor elvégzi az alapvető példányosításokat és a signalok összekapcsolását.
 */
class Application : public QApplication
{
    Q_OBJECT
public:
    /** Konstruktor. Alapvető példányosítások és signal bekötések. */
    Application(int argc, char *argv[]);
    ~Application() = default;

private:
    QQmlApplicationEngine engine;
    CommunicationTcpSocketServer tcpServer;
    CommunicationTcpSocketClient tcpClient;
    DataParser dataParser;
    CommunicationSerialPort serialPort;
    QTimer* dataUpdateTimer;
    WindowsEventHandler eventhandler;

    QQuickItem* findItemByName(const QString& name);
    QQuickItem* findItemByName(QObject *rootObject, const QString& name);
    QQuickItem* findItemByName(QList<QObject*> nodes, const QString& name);
    QQuickItem* mainWindowObject;

public slots:
    void errorHandling(const QString&);
<<<<<<< HEAD
    void tmp();
=======
    void dataTimeout();
>>>>>>> sandbox-koincidencia
};

#endif // STVAPPLICATION_H
