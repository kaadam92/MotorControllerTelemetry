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
