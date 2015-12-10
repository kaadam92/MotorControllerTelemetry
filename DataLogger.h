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
     * @param logFilePath   A log fájl elérési útja.
     * @param logFileStylePath  A stílust leíró fájl elérési útja.
     * @param strLogFilePath    A szöveges üzeneteket tároló fájl elérési útja.
     */
    DataLogger(const QString& logFilePath, const QString& logFileStylePath, const QString& strLogFilePath);
    /** @brief Destruktor.
     *
     * Elmenti a fájlokat, nehogy lezáratlanul maradjanak egy program elszállás esetén.
     */
    ~DataLogger();
private:
    /** @brief Fájlba írás timer.
     *
     * Minden timeoutkor lekérjük az adatokat és elmentjük a megfelelő fájlba.
     * @warning Ha túl gyakran írunk, az a program nagyfokú lassulását okozza!
     */
    QTimer loggerTimer;
    QFile logFile, logFileStyle, strLogFile;

    /** @brief A kiírás sorrendjét tartalmazó vector.
     *
     * A logFileStyle fájlból kiolvasott fejléc alapján elmentjük a fejléc stringjeit.
     * Ezek a karakterláncok fognak a megkapott adat tároló kulcsaként szolgálni. @see DataParser::dataMap
     **/
    QVector<QString> printOrder;

    /** @brief A log fájlokba beleírja a fejlécet. Initkor hívódik meg.*/
    void printLogFileHeader();

signals:
    /** @brief Hibakezelés.*/
    void errorOccurred(const QString&);
    /** @brief Megkéri a DataParsert, hogy küldje el a várakozási sorokat tartalmazó jelet. @see DataParser::giveQueue()*/
    void getDataToLog();

public slots:
    /** @brief A DataParser::giveQueue() jelét fogadja az adatokkal.*/
    void saveToLog(QQueue<QSharedPointer<QString>>&, QQueue<QSharedPointer<QMap<QString, double>>>&,
                   QQueue<QSharedPointer<QDateTime>>&, QQueue<QSharedPointer<QDateTime>>&);
private slots:
    /** @brief Ha lejár a timer kibocsájtja az adatlekérő jelet.*/
    void loggerTimerTimeout(){emit getDataToLog();}
};
