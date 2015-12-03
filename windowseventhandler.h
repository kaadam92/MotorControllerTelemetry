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
    WindowsEventHandler(QQmlContext &qmlContext, auto rootObject);

    ~WindowsEventHandler() = default;

    //void ConnectQmlSignals(QObject *rootObject);

public slots:
    void connectCommand();
    void stopCommand();
    void driveEnableCommand();
    void hvEnableCommand();

private:

    auto rootObject = rootObject;

    QQmlContext &qmlContext;
    QQuickItem* findItemByName(const QString& name);
    QQuickItem* findItemByName(QObject *rootObject, const QString& name);
    QQuickItem* findItemByName(QList<QObject*> nodes, const QString& name);

};

#endif // WINDOWSEVENTHANDLER_H
