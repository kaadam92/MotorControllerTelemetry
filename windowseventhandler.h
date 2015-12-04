#pragma once

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include <QQmlContext>
#include <QDebug>
#include <QQuickItem>
#include <QMap>
#include <QVector>
#include <QDateTime>
#include <QTimer>
#include "qcustomplot.h"

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

    /** A plot pointert lehet beállítani vele.*/
    void setPtr(QCustomPlot* ptr){plotPtr = ptr;}

signals:
    /** Hatására meg kell történjen az új adatok betöltése a paraméterként
     * átadott asszociatív tárolóban.*/
    void getData(QMap<QString, QVector<double>>&);

public slots:
    void connectCommand();
    void stopCommand();
    void driveEnableCommand();
    void hvEnableCommand();

    /** Hatására emittálódik a getData(...) signal.*/
    void replotTimeout(){emit getData(dataVectorMap);}
    /** Hatására az adatoknak megfelelően újrarajzolódik a grafikon.
     * Új adatok felvétele után ajánlott használni.*/
    void replot();

private:
    QQmlContext &qmlContext;

    /** A grafikonra rajzolandó adatokat tartalmazó asszociatív tároló.*/
    QMap<QString, QVector<double>> dataVectorMap;
    /** A grafikon időtengelyét leképező vektor.*/
    QVector<double> timeVec;
    /** Új adatok beolvasásához és újrarajzoláshoz használt timer.*/
    QTimer replotTimer;
    /** Ez a pointer mutat a QML felületen létrejövő grafikonra.*/
    QCustomPlot* plotPtr;



};

