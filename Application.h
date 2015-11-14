#pragma once
#ifndef STVAPPLICATION_H
#define STVAPPLICATION_H
#include <QApplication>
#include <QQmlApplicationEngine>
#include "mainwindow.h"
#include "Communication/CommunicationTcpSocketServer.h"

/**
 * @brief Alkalmazás osztály. A main() példányosítja és indítja el.
 *
 * A konstruktor elvégzi az alapvető példányosításokat és a signalok összekapcsolását.
 */
class Application : public QApplication
{
public:
    /** Konstruktor. Alapvető példányosítások és signal bekötések. */
    Application(int argc, char *argv[]);
    ~Application() = default;

private:
    QQmlApplicationEngine engine;
    CommunicationTcpSocketServer tcpServer;
protected slots:
    void dataReceived(QDataStream&);
};

#endif // STVAPPLICATION_H
