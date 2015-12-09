#include "Application.h"

/** A szerver hallgatózás az inicializáláskor megkezdődik.
 *
 */

const double checkTabTimerInterval = 1000;
const double dataUpdateTimerInterval = 1000;

Application::Application(int argc, char *argv[])
    : QApplication(argc, argv),
      engine(),
      tcpClient(),
      dataParser(QString("code.txt")),
      serialPort(QString("COM4"),QSerialPort::Baud9600,QSerialPort::Data8,QSerialPort::NoParity,QSerialPort::OneStop),
      eventhandler(*engine.rootContext()),
      dataLogger("log/log.csv", "log/logstyle.txt", "log/strlog.csv")
{
    generateQMLData();
    initQML();
    makeConnections();
    initTimers();
}

void Application::initQML()
{
    /** A QML-Cpp kommunikációhoz használt QMLData obejktumokat létre kell
     *  hozni a QML felület számára.*/
    QMap<QString,QMLData>::iterator iter;
    for(iter = qmlDataMap.begin(); iter != qmlDataMap.end(); ++iter)
    {
        engine.rootContext()->setContextProperty(iter.key(), &iter.value());
    }

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    auto rootObjects = engine.rootObjects();

    if (rootObjects.size() == 0)
    {
        qWarning() << "HIBA: Nem sikerült létrehozni a QML környezetet.";
    }

    rootObject = rootObjects.first();
    customPlotPtr = (QCustomPlot*)rootObject->findChild<QObject*>("customPlot");

    auto mainWindowPtr = rootObject->findChild<QObject*>("MainWindow");
    eventhandler.setMainWindowPtr(mainWindowPtr);

    QObject::connect(rootObject, SIGNAL(connectCommandCpp()),
                     &eventhandler, SLOT(connectCommand()));
    QObject::connect(rootObject, SIGNAL(connectCommandCpp()),
                     this, SLOT(connectToServer()));

    QObject::connect(rootObject, SIGNAL(hvEnableCommandCpp()),
                     &eventhandler, SLOT(hvEnableCommand()));
    QObject::connect(rootObject, SIGNAL(hvEnableCommandCpp()),
                     this, SLOT(hvenCommand()));

    QObject::connect(rootObject, SIGNAL(driveEnableCommandCpp()),
                     &eventhandler, SLOT(driveEnableCommand()));
    QObject::connect(rootObject, SIGNAL(driveEnableCommandCpp()),
                     this, SLOT(drenCommand()));

    QObject::connect(rootObject, SIGNAL(stopCommandCpp()),
                     &eventhandler, SLOT(stopCommand()));
    QObject::connect(rootObject, SIGNAL(stopCommandCpp()),
                     this, SLOT(stopCommand()));
}

void Application::makeConnections()
{
    /** Kommunikációs signalok-slotok.*/
    connect(&tcpClient,SIGNAL(dataReady(QDataStream&)),
            &dataParser,SLOT(dataInput(QDataStream&)));
    connect(&serialPort,SIGNAL(dataReady(QDataStream&)),
            &dataParser,SLOT(dataInput(QDataStream&)));

    connect(&tcpClient,SIGNAL(errorOccurred(const QString&)),
            this,SLOT(errorHandling(const QString&)));
    connect(&dataParser,SIGNAL(errorOccurred(const QString&)),
            this,SLOT(errorHandling(const QString&)));
    connect(&serialPort,SIGNAL(errorOccurred(const QString&)),
            this,SLOT(errorHandling(const QString&)));

    /** A grafikon datainak frissítésért felelős signalok-slotok.*/
    QObject::connect(&eventhandler,SIGNAL(getData(QMap<QString,QVector<double>>&)),
                     &dataParser,SLOT(getData(QMap<QString,QVector<double>>&)));
    QObject::connect(&dataParser,SIGNAL(newToPlot()),
                     &eventhandler,SLOT(replot()));

    /** GUI string kijelzéshez tartozó signalok-slotok.*/
    QObject::connect(&dataParser, SIGNAL(newString(QSharedPointer<QString>)),
                     &eventhandler, SLOT(stringMessage(QSharedPointer<QString>)));

    /** A loggolásért felelős jelek összekötése.*/
    QObject::connect(&dataLogger, SIGNAL(getDataToLog()),
                     &dataParser, SLOT(getQueues()));
    QObject::connect(&dataParser, SIGNAL(giveQueue(QQueue<QSharedPointer<QString> >&, QQueue<QSharedPointer<QMap<QString,double> > >&, QQueue<QSharedPointer<QDateTime> >&, QQueue<QSharedPointer<QDateTime> >&)),
                     &dataLogger, SLOT(saveToLog(QQueue<QSharedPointer<QString> >&, QQueue<QSharedPointer<QMap<QString,double> > >&, QQueue<QSharedPointer<QDateTime> >&, QQueue<QSharedPointer<QDateTime> >&)));
}

void Application::initTimers()
{
    /** Mivel a grafikont tartalmazó tab csak kattintás után jön létre,
     * ezért a rá mutató pointert csak ez után lehet létrehozni.
     * Minden timer timeoutkor megvizsgáljuk, hogy lekérhető-e a pointer.*/
    QObject::connect(&checkTabTimer,SIGNAL(timeout()),
                     this,SLOT(checkTab()));
    checkTabTimer.setInterval(checkTabTimerInterval);
    checkTabTimer.start();
    /** A cellafeszültségeket, más adatokat is frissíteni kell.*/
    QObject::connect(&dataUpdateTimer, SIGNAL(timeout()),
                     this, SLOT(updateData()));
    dataUpdateTimer.setInterval(dataUpdateTimerInterval);
    dataUpdateTimer.start();
}

void Application::generateQMLData()
{
    QMap<quint16, QString> codeMap = dataParser.getCodeMap();
    QMap<quint16, QString>::iterator iter;

    for(iter = codeMap.begin(); iter != codeMap.end(); ++iter)
    {
        QMLData tmpData(2500);
        qmlDataMap[iter.value()] = tmpData;
    }
}

void Application::checkTab()
{
    if(customPlotPtr == nullptr)
    {
        CustomPlotItem* cpiPtr = (CustomPlotItem*)rootObject->findChild<QObject*>("customPlot");
        if(cpiPtr != nullptr)
        {
            customPlotPtr = cpiPtr->getPtr();
        }
        if(customPlotPtr != nullptr)
        {
            qDebug() << "Megvan a grafikon tab!! Köszi a klikket!";
            eventhandler.setPlotPtr(customPlotPtr);
            checkTabTimer.stop();
        }
        else
        {
             qDebug() << "Nincs meg a grafikon tab!! Kattintsál mán...";
        }
    }
}

void Application::updateData()
{
    QMap<QString, double> dataMap = dataParser.getDataMap();
    QMap<QString, double>::iterator iter;
    for(iter = dataMap.begin(); iter != dataMap.end(); ++iter)
    {
        qmlDataMap[iter.key()].setData(iter.value());
    }
}

void Application::errorHandling(const QString& error)
{
    qWarning() << "Hiba!";
    qWarning() << error;
}

void Application::sendData(quint16 code, double value)
{
    QByteArray ba(reinterpret_cast<const char*>(&code), sizeof(quint16));
    QByteArray byteArray(reinterpret_cast<const char*>(&value), sizeof(double));
    ba.insert(2,byteArray);
    tcpClient.send(ba);
}

void Application::connectToServer()
{
    /** Kommunikáció indítása, kapcsolódás.*/
    tcpClient.connect(QString("localhost"),4444);
    serialPort.connect();
}

void Application::hvenCommand()
{
    sendData(dataParser.getCode("state"), 10);
}

void Application::drenCommand()
{
    sendData(dataParser.getCode("state"), 20);
    sendData(dataParser.getCode("vref"), 35);
}

void Application::stopCommand()
{
    sendData(dataParser.getCode("state"), 0);
}
