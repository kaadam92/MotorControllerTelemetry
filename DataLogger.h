#pragma once

#include <QObject>
#include <QString>
#include <QTimer>
#include <QQueue>
#include <QMap>
#include <QFile>
#include <QDateTime>
#include <QTextStream>
#include <QVector>
#include <QDebug>
#include <QSharedPointer>

/** @brief Az érkezett adatok és szöveges üzenetek fájlba mentéséért felelős objektum.
 *
 * A loggerTimer lejártakor kibocsájtásra kerül a getDataToLog() jel, ami a DataParser objektumot
 * a várakozási sorainak elküldésére szólítja fel, így a saveToLog slot fog meghívódni.
 *
 * Az így kapott adatokat az időbélyegekkel együtt a megadott helyre és formában írjuk ki .csv formátumban.
 *
 * A logFileStyle fájlban meg lehet adni, hogy mely adatokat, milyen sorrendben írja ki az objektum.
 * Gyakorlatilag a csv fájlok fejlécét kell megadni, a fejlécek neve meg kell egyezzen a jelentés-kód fájlok
 * jelentés stringjével(@see DataParser::codeFile). Így a mentésre kerülő adatok száma, sorrendje testreszabható.
 *
 * A log fájlok nevébe beágyazásra kerül a létrehozás időpontja, így nem íródnak felül a régebbi adatok.
 */
class DataLogger : public QObject
{
    Q_OBJECT
public:
    /** @brief Konstruktor.
     *
     *
     */
    DataLogger(const QString&, const QString&, const QString&);
    ~DataLogger();
private:
    QTimer loggerTimer;
    QFile logFile, logFileStyle, strLogFile;
    QVector<QString> printOrder;

    void printLogFileHeader();
signals:
    void errorOccurred(const QString&);
    void getDataToLog();

public slots:
    void saveToLog(QQueue<QSharedPointer<QString>>&, QQueue<QSharedPointer<QMap<QString, double>>>&,
                   QQueue<QSharedPointer<QDateTime>>&, QQueue<QSharedPointer<QDateTime>>&);
private slots:
    void loggerTimerTimeout(){emit getDataToLog();}
};
