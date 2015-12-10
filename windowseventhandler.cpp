#include "windowseventhandler.h"

const int replotTimerInterval = 100;
const int timeVecToDisplay = 100;

WindowsEventHandler::WindowsEventHandler(QQmlContext &qmlContext)
    :qmlContext(qmlContext)
{
    plotPtr = nullptr;
    mainWindowPtr = nullptr;

    /** Újrarajzoló időzítés inicializálása.*/
    connect(&replotTimer, SIGNAL(timeout()),
            this, SLOT(replotTimeout()));
    replotTimer.setInterval(replotTimerInterval);
}


void WindowsEventHandler::logPost(QVariant text, QVariant color)
{
    QVariant returnedValue;
    QVariant messageText = text;
    QVariant outputcolor = color;
    QMetaObject::invokeMethod(mainWindowPtr, "selectColor",
        Q_RETURN_ARG(QVariant, returnedValue),
        Q_ARG(QVariant, messageText),
        Q_ARG(QVariant, outputcolor));
}

void WindowsEventHandler::setMainWindowPtr(QObject* ptr)
{
    mainWindowPtr = ptr;
}

void WindowsEventHandler::stringMessage(QSharedPointer<QString> strPtr)
{
    if(strPtr->contains("selftest", Qt::CaseInsensitive))
    {
        if(strPtr->contains("ok", Qt::CaseInsensitive))
        {
            logPost(*strPtr, "green");
        }
        else if(strPtr->contains("fault", Qt::CaseInsensitive))
        {
            logPost(*strPtr, "red");
        }
        else
        {
            logPost(*strPtr, "orange");
        }
    }
    else
    {
        logPost(*strPtr, "blue");
    }
    strPtr.clear();
}

void WindowsEventHandler::connectCommand()
{
    qDebug() << "Connect gomb megnyomva.";
    replotTimer.start();
}

void WindowsEventHandler::hvEnableCommand()
{
    qDebug() << "HV enable gomb megnyomva.";
    replotTimer.start();
}

void WindowsEventHandler::driveEnableCommand()
{
    qDebug() << "Drive Enable gomb megnyomva.";
    replotTimer.start();
}

void WindowsEventHandler::stopCommand()
{
    qDebug() << "Stop gomb megnyomva.";
}

void WindowsEventHandler::replot()
{
    timeVec.append(QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0);
    // Ha nincs még plot felület (még nem jött létre, mert sosem jelent még meg), akkor ne próbáljunk meg rajzolni
    if(plotPtr != nullptr)
    {
        //Ha nincs elég grafikon, akkor sem érdemes rajzolni.
        if(plotPtr->graphCount() >= 2)
        {
            plotPtr->graph(0)->setData(timeVec,dataVectorMap["speed"]);
            plotPtr->graph(1)->setData(timeVec,dataVectorMap["vref"]);
            if(timeVec.size() < timeVecToDisplay)
                plotPtr->xAxis->setRange(timeVec.first(), timeVec.last());
            else
            {
                QVector<double>::iterator i = timeVec.end();
                i-=timeVecToDisplay;
                plotPtr->xAxis->setRange(*(i), timeVec.last());
            }
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

