#include "mainwindow.h"
#include <QApplication>
#include <Communication/CommunicationTcpSocketServer.h>
#include <Application.h>
#include <QtQuick>
#include <QQmlContext>
#include <QDebug>
#include <QQmlApplicationEngine>
#include "customplotitem.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<CustomPlotItem>("CustomPlot", 1, 0, "CustomPlotItem");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    auto rootObjects = engine.rootObjects();
    if (rootObjects.size() == 0)
    {
        qDebug() << "HIBA: Nem sikerült létrehozni a QML környezetet.";
        return 0;
    }




    return app.exec();
}
