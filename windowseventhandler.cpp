#include "windowseventhandler.h"
#include <QQmlContext>
#include <QQmlApplicationEngine>

WindowsEventHandler::WindowsEventHandler( QQmlContext &qmlContext)
    :qmlContext(qmlContext)
{

}

void WindowsEventHandler::connectCommand()
{
    qDebug() << "Connect gomb megnyomva.";
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
