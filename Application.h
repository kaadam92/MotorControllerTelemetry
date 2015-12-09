#pragma once
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QString>
#include <QVector>
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QMap>
#include <QSharedPointer>
#include <QtGlobal>
#include "DataParser.h"
#include "mainwindow.h"
#include "Communication/CommunicationTcpSocketServer.h"
#include "Communication/CommunicationTcpSocketClient.h"
#include "Communication/CommunicationSerialPort.h"
#include "windowseventhandler.h"
#include "qcustomplot.h"
#include "customplotitem.h"
#include "DataLogger.h"
#include "QMLData.h"

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
    CommunicationTcpSocketClient tcpClient;
    DataParser dataParser;
    CommunicationSerialPort serialPort;
    WindowsEventHandler eventhandler;
    DataLogger dataLogger;

    QMap<QString,QMLData> qmlDataMap;

    QObject *rootObject;
    QCustomPlot* customPlotPtr;

    QTimer checkTabTimer;


    void sendData(quint16 code, double value);
    void initQML();
    void makeConnections();
    void initTimers();
    void generateQMLData();


private slots:
    void checkTab();

public slots:
    void errorHandling(const QString&);
    void connectToServer();
    void hvenCommand();
    void drenCommand();
    void stopCommand();
    void vdemandChanged(QVariant);
};
