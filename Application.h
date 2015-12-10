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
#include "QCustomPlot/qcustomplot.h"
#include "customplotitem.h"
#include "DataLogger.h"
#include "QMLData.h"

/**
 * @brief Alkalmazás osztály. A main() példányosítja és indítja el.
 *
 * A konstruktor elvégzi az alapvető példányosításokat és a signalok összekapcsolását.
 *
 * Minden más objektum itt jön létre, biztosítja a kommunikációt közöttük.
 */

class Application : public QApplication
{
    Q_OBJECT

public:
    /** @brief Konstruktor.
     *
     * Példányosítja a QMLData objektumokat (@see QMLData), inicializálja a QML felületet,
     * létrehozza a signal-slot összeköttetéseket és elindítja a timereket.
     */
    Application(int argc, char *argv[]);
    ~Application() = default;

private:
    QQmlApplicationEngine engine;
    CommunicationTcpSocketClient tcpClient;
    DataParser dataParser;
    CommunicationSerialPort serialPort;
    WindowsEventHandler eventhandler;
    DataLogger dataLogger;

    /** @brief A QML obejktumokat tároló asszociatív tároló. @see QMLData*/
    QMap<QString,QMLData> qmlDataMap;

    /** @brief A grafikus felület gyökérelemére mutató pointer. A grafikon eléréséhez van rá szükség.*/
    QObject *rootObject;
    /** @brief A graikonra mutató pointer.*/
    QCustomPlot* customPlotPtr;

    QTimer checkTabTimer, dataUpdateTimer;

    /**
     * @brief Adatküldés az eszköz felé
     * @details Ezen függvény hívásásval megfelelő ID-jú és tartalmú üzenetet továbbíthaunk
     * az eszköz felé
     *
     * @param code Az üzenet azonostására szolgáló ID
     * @param value Az üzenet tartalma.
     */
    void sendData(quint16 code, double value);

    void initQML();
    void makeConnections();
    void initTimers();
    void generateQMLData();

private slots:
    /** @brief Lellenőrzi, hogy létrejött-e már a grafikon.*
     *
     * Mivel a grafikon csak az első megjelenéskör jön létre, ezért a pointerét nem lehet beállítani, csak az első megjelenés után.
     * A checkTabTimer lejártakor ellenőrzi le a a grafikon létezését, ha létrejött lekéri a pointert és leállítja a timert.
     **/
    void checkTab();

public slots:
    /** @brief Frissíti a qmlDataMap tárolóban levő objektumok értéket a fogadott adatok alapján.*/
    void updateData();
    /** @brief Hibakezelés.*/
    void errorHandling(const QString&);
    void connectToServer();
    void connectedToServer();
    void hvenCommand();
    void drenCommand();
    void stopCommand();
    void testCommand();
    /** @brief Sebesség alapjel fogadása a QML slidertől.*/
    void vdemandChanged(QVariant);
};
