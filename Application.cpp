#include "Application.h"

/** A szerver hallgatózás az inicializáláskor megkezdődik.
 *
 */
Application::Application(int argc, char *argv[])
    : QApplication(argc, argv), engine(),
      tcpServer(4444), tcpClient(),
      dataParser(QString("code.txt")),
      serialPort(QString("COM4"),QSerialPort::Baud9600,QSerialPort::Data8,QSerialPort::NoParity,QSerialPort::OneStop),
      eventhandler(*engine.rootContext())
{

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    auto rootObjects = engine.rootObjects();
    if (rootObjects.size() == 0)
    {
        qDebug() << "HIBA: Nem sikerült létrehozni a QML környezetet.";
    }

    QObject *rootObject = rootObjects[0];

    //eventhandler.ConnectQmlSignals(rootObject);




    connect(&tcpServer,SIGNAL(dataReady(QDataStream&)),
            &dataParser,SLOT(dataInput(QDataStream&)));
    connect(&tcpClient,SIGNAL(dataReady(QDataStream&)),
            &dataParser,SLOT(dataInput(QDataStream&)));
    connect(&serialPort,SIGNAL(dataReady(QDataStream&)),
            &dataParser,SLOT(dataInput(QDataStream&)));

    connect(&tcpServer,SIGNAL(errorOccurred(const QString&)),
            this,SLOT(errorHandling(const QString&)));
    connect(&tcpServer,SIGNAL(errorOccurred(const QString&)),
            this,SLOT(errorHandling(const QString&)));
    connect(&dataParser,SIGNAL(errorOccurred(const QString&)),
            this,SLOT(errorHandling(const QString&)));
    connect(&serialPort,SIGNAL(errorOccurred(const QString&)),
            this,SLOT(errorHandling(const QString&)));

    QObject::connect(rootObject, SIGNAL(connectCommandCpp()),
                     &eventhandler, SLOT(connectCommand()));
    QObject::connect(rootObject, SIGNAL(hvEnableCommandCpp()),
                     &eventhandler, SLOT(hvEnableCommand()));
    QObject::connect(rootObject, SIGNAL(driveEnableCommandCpp()),
                     &eventhandler, SLOT(driveEnableCommand()));
    QObject::connect(rootObject, SIGNAL(stopCommandCpp()),
                     &eventhandler, SLOT(stopCommand()));

    /** Kommunikáció indítása, kapcsolódás.*/
    tcpClient.connect(QString("localhost"),4444);
    serialPort.connect();

    /** Adat frissítés timer indítása.*/
    dataUpdateTimer = new QTimer(this);
    dataUpdateTimer->stop();
    connect(dataUpdateTimer,SIGNAL(timeout()),
            &dataParser,SLOT(saveDataTimestamp()));

    /** Folyamatos timer legyen.*/
    dataUpdateTimer->setSingleShot(false);
    dataUpdateTimer->setInterval(500);
    dataUpdateTimer->start();
}

void Application::errorHandling(const QString& error)
{
    qWarning() << "Hiba!";
    qWarning() << error << endl;
}
