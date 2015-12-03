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


    qmlRegisterType<CustomPlotItem>("CustomPlot", 1, 0, "CustomPlotItem");

    Application app(argc, argv);



    return app.exec();
}
