#include "windowseventhandler.h"

const int replotTimerInterval = 100;

WindowsEventHandler::WindowsEventHandler(QQmlContext &qmlContext)
    :qmlContext(qmlContext)
{
//    auto rootObjects = engine.rootObjects();
//    if (rootObjects.size() == 0)
//    {
//        qDebug() << "HIBA: Nem sikerült létrehozni a QML környezetet.";
//    }
//
//    QObject *rootObject = rootObjects[0];

    plotPtr = nullptr;
    /** Újrarajzoló időzítés inicializálása.*/
    connect(&replotTimer, SIGNAL(timeout()),
            this, SLOT(replotTimeout()));
    replotTimer.setInterval(replotTimerInterval);
    //replotTimer.start();
}



void WindowsEventHandler::connectCommand()
{
    qDebug() << "Connect gomb megnyomva.";
    replotTimer.start();
}

void WindowsEventHandler::hvEnableCommand()
{
    qDebug() << "HV enable gomb megnyomva.";
}

void WindowsEventHandler::driveEnableCommand()
{
    qDebug() << "Drive Enable gomb megnyomva.";
}

void WindowsEventHandler::stopCommand()
{
    qDebug() << "Stop gomb megnyomva.";
    replotTimer.stop();
}

void WindowsEventHandler::replot()
{
    timeVec.append(QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0);
    if(plotPtr != nullptr)
    {
        if(plotPtr->graphCount() >= 2)
        {
            plotPtr->graph(0)->setData(timeVec,dataVectorMap["speed"]);
            plotPtr->graph(1)->setData(timeVec,dataVectorMap["vref"]);
            if(timeVec.size() < 100)
                plotPtr->xAxis->setRange(timeVec.first(), timeVec.last());
            else
            {
                QVector<double>::iterator i = timeVec.end();
                i-=100;
                plotPtr->xAxis->setRange(*(i), timeVec.last());
            }
            //plotPtr->yAxis->setRange(-20, 55);
            plotPtr->replot();
        }
        else
        {
            qDebug() << "Nincse elég graph, nem lehet plottolni.";
        }
    }
    else
    {
        qDebug() << "Replottolnék én, csak még nincs hová...";
    }
}

/*
void MainWindowsEventHandler::historyChanged()
{
    // Ahhoz, hogy frissüljenek a QML oldali adatok, frissíteni kell a változók összekapcsolását.
    qmlContext.setContextProperty(QStringLiteral("historyModel"), QVariant::fromValue(history.stateList));
    qmlContext.setContextProperty(QStringLiteral("currentState"), QVariant::fromValue(history.currentState));

    qmlContext.setContextProperty(QStringLiteral("historyGraphTimestamps"), QVariant::fromValue(history.graphTimestamps));
    qmlContext.setContextProperty(QStringLiteral("historyGraphVelocity"), QVariant::fromValue(history.graphVelocities));
    qmlContext.setContextProperty(QStringLiteral("historyGraphAcceleration"), QVariant::fromValue(history.graphAcceleration));

    // Jelzünk a QML controloknak, hogy újrarajzolhatják magukat, beállítottuk az új értékeket.
    emit historyContextUpdated();
}
*/
/*
QQuickItem* WindowsEventHandler::findItemByName(const QString& name)
{
    Q_ASSERT(mainWindowObject != nullptr);
    if (mainWindowObject->objectName() == name)
    {
        return mainWindowObject;
    }
    return findItemByName(mainWindowObject->children(), name);
}


QQuickItem* WindowsEventHandler::findItemByName(QObject *rootObject, const QString& name)
{
    Q_ASSERT(rootObject != nullptr);
    if (rootObject->objectName() == name)
    {
        return (QQuickItem*)rootObject;
    }
    return findItemByName(rootObject->children(), name);
}

QQuickItem* WindowsEventHandler::findItemByName(QList<QObject*> nodes, const QString& name)
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
*/
