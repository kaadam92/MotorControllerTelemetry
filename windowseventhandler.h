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
#include "QCustomPlot/qcustomplot.h"

class QQuickItem;
class QQmlContext;
class QQmlApplicationEngine;


/**
 * @brief Az ablak eseménykezelőit megvalósító osztály.
 *
 * Ebbe az osztályba vannak ketötve a QML felől érkező signalok, illetve szintén
 * ez az osztály felelős a digaram megfelelő időközönkénti újrarajzolásáért.
 *
 */

class WindowsEventHandler : public QObject
{
    Q_OBJECT

public:
    WindowsEventHandler(QQmlContext &qmlContext);

    //~WindowsEventHandler() = default;

    //void ConnectQmlSignals(QObject *rootObject);

    /**
     * @brief Beállítja a grafikonra mutató pointert.
     * @details A QML-ben példányosított QCustomPlot-ra mutató pointert állítja be az osztályon belül.
     * Azét van rá szükség, mert az Application osztály hozza létre a QML contextet, de a pointerre itt kell
     * 
     * @param ptr A QCustomPlotItemre mutató pointer
     */
    void setPlotPtr(QCustomPlot* ptr){plotPtr = ptr;}

    /**
     * @brief Beállítja az UI főablakára mutató pointert.
     * @details A QML-ben példányosított UI főablakra mutató pointert állítja be az osztályon belül.
     * Azét van rá szükség, mert az Application osztály hozza létre a QML contextet, de a pointerre itt kell
     * 
     * @param ptr Az UI főablakára mutató pointer
     */
    void setMainWindowPtr(QObject* ptr);

    /**
     * @brief Az UI-on található log felületre ír ki egy üzenetet.
     * @details A szöveg tetszőleges string, a szín segítségével pedig egyes kategóriákat lehet megkülönbözetni (pl. piros ERROR)
     * 
     * @param text Az üzenet szövege
     * @param color Az üzenet jelölő színe
     */
    void logPost(QVariant text, QVariant color);

signals:
    /** Hatására meg kell történjen az új adatok betöltése a paraméterként
     * átadott asszociatív tárolóban.*/
    void getData(QMap<QString, QVector<double>>&);
    void contextUpdated();

public slots:
    void stringMessage(QSharedPointer<QString>);
    void connectCommand();
    void stopCommand();
    void driveEnableCommand();
    void hvEnableCommand();
    void historyChanged();

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
    QObject* mainWindowPtr;



};

