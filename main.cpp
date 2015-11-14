#include "mainwindow.h"
#include <QApplication>
#include <Communication/CommunicationTcpSocketServer.h>
#include <Application.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    Application a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
