#include "Application.h"

/** A szerver hallgatózás az inicializáláskor megkezdődik.
 *
 */
Application::Application(int argc, char *argv[])
    : QApplication(argc, argv),
      engine(),
      //tcpServer(4444),
      tcpClient(),
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

    /** Kommunikációs signalok-slotok.*/
//    connect(&tcpServer,SIGNAL(dataReady(QDataStream&)),
//            &dataParser,SLOT(dataInput(QDataStream&)));
    connect(&tcpClient,SIGNAL(dataReady(QDataStream&)),
            &dataParser,SLOT(dataInput(QDataStream&)));
    connect(&serialPort,SIGNAL(dataReady(QDataStream&)),
            &dataParser,SLOT(dataInput(QDataStream&)));

//    connect(&tcpServer,SIGNAL(errorOccurred(const QString&)),
//            this,SLOT(errorHandling(const QString&)));
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

    /** Mivel a grafikont tartalmazó tab csak kattintás után jön létre,
     * ezért a rá mutató pointert csak ez után lehet létrehozni.
     * Minden timer timeoutkor megvizsgáljuk, hogy lekérhető-e a pointer.*/
    QObject::connect(&checkTabTimer,SIGNAL(timeout()),
                     this,SLOT(checkTab()));
    checkTabTimer.setInterval(1000);
    checkTabTimer.start();
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
void Application::errorHandling(const QString& error)
{
    qWarning() << "Hiba!";
    qWarning() << error << endl;
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
    sendData(dataParser.getCode("hven"), 10);
}

void Application::drenCommand()
{
    sendData(dataParser.getCode("dren"), 10);
    sendData(dataParser.getCode("vref"), 10);
}

void Application::stopCommand()
{
    sendData(dataParser.getCode("stop"), 10);
}
