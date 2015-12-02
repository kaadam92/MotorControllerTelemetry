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
