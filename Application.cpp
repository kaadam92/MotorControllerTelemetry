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

    mainWindowObject = findItemByName(rootObject, QString("ApplicationWindow"));
    if (!mainWindowObject)
    {
        qDebug() << "Nem találom a ApplicationWindow objektumot.";
    }

    //auto qmlObject = rootObject -> findChildren<QObject*>();
    auto qmlObject = rootObject -> findChild<QObject*>(QString("graphCustomPlot"));
    //qmlObject = qmlObject -> findChild<QObject*>(QString("graphTab"));
    //qmlObject = qmlObject -> findChild<QObject*>(QString("graphTabItem"));
    //qmlObject = qmlObject -> findChild<QObject*>(QString("graphCustomPlot"));

    QList<CustomPlotItem*> lista = rootObject->findChildren<CustomPlotItem*>();
    //CustomPlotItem* myplot = rootObject->findChild<CustomPlotItem*>("CustomPlotItem").SayBMEG();


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
    rootObject->
    /** Kommunikáció indítása, kapcsolódás.*/
    //tcpClient.connect(QString("localhost"),4444);
    //serialPort.connect();

    /** Adat frissítés timer indítása.*/
    dataUpdateTimer = new QTimer(this);
    dataUpdateTimer->stop();

    /** Folyamatos timer legyen.*/
    dataUpdateTimer->setSingleShot(false);
    dataUpdateTimer->setInterval(5000);
    dataUpdateTimer->start();
    //dataUpdateTimer = new QTimer(this);
    //dataUpdateTimer->stop();

    connect(dataUpdateTimer,SIGNAL(timeout()),
            this,SLOT(dataTimeout()));
    connect(this,SIGNAL(getData(QMap<QString,QVector<double> >&)),
            &dataParser,SLOT(getData(QMap<QString, QVector<double>>&)));
    connect(&dataParser,SIGNAL(newToPlot()),
            &eventhandler,SLOT(refreshPlot()));

    /** Folyamatos timer legyen.*/
    //dataUpdateTimer->setSingleShot(false);
    //dataUpdateTimer->setInterval(500);
    //dataUpdateTimer->start();
}

void Application::dataTimeout()
{
    //emit getData(dataVectorMap);
}

void Application::errorHandling(const QString& error)
{
    qWarning() << "Hiba!";
    qWarning() << error << endl;
}

QQuickItem* Application::findItemByName(const QString& name)
{
    Q_ASSERT(mainWindowObject != nullptr);
    if (mainWindowObject->objectName() == name)
    {
        return mainWindowObject;
    }
    return findItemByName(mainWindowObject->children(), name);
}

QQuickItem* Application::findItemByName(QObject *rootObject, const QString& name)
{
    Q_ASSERT(rootObject != nullptr);
    if (rootObject->objectName() == name)
    {
        return (QQuickItem*)rootObject;
    }
    return findItemByName(rootObject->children(), name);
}

QQuickItem* Application::findItemByName(QList<QObject*> nodes, const QString& name)
{
    for(int i = 0; i < nodes.size(); i++)
    {
        // Node keresése
        if (nodes.at(i) && nodes.at(i)->objectName() == name)
        {
            return dynamic_cast<QQuickItem*>(nodes.at(i));
        }
        // Gyerekekben keresés
        else if (nodes.at(i) && nodes.at(i)->children().size() > 0)
        {
            QQuickItem* item = findItemByName(nodes.at(i)->children(), name);
            if (item)
                return item;
        }
    }
    // Nem találtuk.
    return nullptr;
}
