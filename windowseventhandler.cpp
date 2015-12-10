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
    mainWindowPtr = nullptr;
    /** Újrarajzoló időzítés inicializálása.*/
    connect(&replotTimer, SIGNAL(timeout()),
            this, SLOT(replotTimeout()));
    replotTimer.setInterval(replotTimerInterval);
    //replotTimer.start();
}


void WindowsEventHandler::logPost(QVariant text, QVariant color){

    QVariant returnedValue;
    QVariant messageText = text;
    QVariant outputcolor = color;
    QMetaObject::invokeMethod(mainWindowPtr, "selectColor",
        Q_RETURN_ARG(QVariant, returnedValue),
        Q_ARG(QVariant, messageText),
        Q_ARG(QVariant, outputcolor));
}

 void WindowsEventHandler::setMainWindowPtr(QObject* ptr){
     mainWindowPtr = ptr;
 }

void WindowsEventHandler::stringMessage(QSharedPointer<QString> strPtr)
{
    logPost(*strPtr, "blue");
    strPtr.clear();
}
 void WindowsEventHandler::historyChanged()
 {
     // Ahhoz, hogy frissüljenek a QML oldali adatok, frissíteni kell a változók összekapcsolását.
     //qmlContext.setContextProperty(QStringLiteral("historyModel"), QVariant::fromValue(history.stateList));


     // Jelzünk a QML controloknak, hogy újrarajzolhatják magukat, beállítottuk az új értékeket.
    // emit historyContextUpdated();
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

