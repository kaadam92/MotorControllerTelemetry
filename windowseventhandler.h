#ifndef WINDOWSEVENTHANDLER_H
#define WINDOWSEVENTHANDLER_H
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include <QQmlContext>
#include <QDebug>

class QQuickItem;
class QQmlContext;
class QQmlApplicationEngine;

class WindowsEventHandler : public QObject
{
    Q_OBJECT

public:
    WindowsEventHandler(QQmlContext &qmlContext);

    ~WindowsEventHandler() = default;

    //void ConnectQmlSignals(QObject *rootObject);

public slots:
    void connectCommand();
    void stopCommand();
    void driveEnableCommand();
    void hvEnableCommand();

private:
    QQmlContext &qmlContext;

};

#endif // WINDOWSEVENTHANDLER_H
