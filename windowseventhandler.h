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

    /**
     * @brief Beállítja a grafikonra mutató pointert.
     * @details A QML-ben példányosított QCustomPlot-ra mutató pointert állítja be az osztályon belül.
     * Azét van rá szükség, mert az Application osztály hozza létre a QML contextet, de a pointerre itt van szükség
     * 
     * @param ptr A QCustomPlotItemre mutató pointer
     */
    void setPlotPtr(QCustomPlot* ptr){plotPtr = ptr;}

    /**
     * @brief Beállítja az UI főablakára mutató pointert.
     * @details A QML-ben példányosított UI főablakra mutató pointert állítja be az osztályon belül.
     * Azét van rá szükség, mert az Application osztály hozza létre a QML contextet, de a pointerre itt van szükség
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
    /** A főablakra mutató pointer.*/
    QObject* mainWindowPtr;

signals:
    /** Hatására meg kell történjen az új adatok betöltése a paraméterként
     * átadott asszociatív tárolóba.*/
    void getData(QMap<QString, QVector<double>>&);

public slots:
    /** @brief A beérkező string üzeneteket fogadja.
     *
     * A paraméterét QSharedPointer-ként fogadja, mivel az adatok fájlba mentésekor megszűnne a rá mutató pointer. @see DataLogger
     * Ha a szövegben megtalálható a "selftest" kifejezés, akkor hiba esetén ("fault") pirossal, rendben lezajló ellenőrzésnél ("ok") zölddel
     * jeleníti meg a stringet. Ha nem találja a "fault" vagy "ok" kifejezést a szöveg színe narancs lesz.
     * Más esetben kék színű szöveg fog megjelenni.
     */
    void stringMessage(QSharedPointer<QString>);
    /** @brief A connect feliratú gomb hatására hívódik meg.*/
    void connectCommand();
    /** @brief A stop feliratú gomb hatására hívódik meg.*/
    void stopCommand();
    /** @brief A drive enable feliratú gomb hatására hívódik meg.*/
    void driveEnableCommand();
    /** @brief A HV enable feliratú gomb hatására hívódik meg.*/
    void hvEnableCommand();

    /** @brief Hatására emittálódik a getData(...) signal.*/
    void replotTimeout(){emit getData(dataVectorMap);}
    /** @brief Hatására az adatoknak megfelelően újrarajzolódik a grafikon.
     *
     * Új adatok felvétele után ajánlott használni.
     */
    void replot();

};

