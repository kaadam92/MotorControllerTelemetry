#pragma once

#include <QObject>
#include <QMap>
#include <QString>
#include <QErrorMessage>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QtMath>
#include <QDateTime>
#include <QQueue>
#include <QSharedPointer>

/** @brief Az kapott adat értelmezéséért, szétbontásáért felelős objektum.
 *
 * A dataInput(...) slotban kapott streamből a saját protokollnak megfeleően
 * elmenti a vett adatokat a dataMap változóba.
 * A dataMap kulcsa az adat jelentését kifejező QString, értéke double szám.
 * Azt, hogy mely jelentéshez milyen 16bites kód tartozik a vett üzenetben a codeMap változó tartalmazza.
 * Erre az adatok vételekor van szükség, így könnyű kikeresni a vett adat bájtok jelentését.
 * Hasonlóan létezik a codeMapInverse tároló, amely a codeMap adatait tartalmazza, csak a kulcs és érték fel vannak cserélve.
 * Előnyös, ha küldeni szeretnénk adatot, ugyanis akkor a string alapján tudjuk kikeresni az elküldendő kódot.
 *
 * A program mellett található code.txt tartalmazza a jelentés-kód párokat, a konstruktor
 * ebból a fájlból olvassa ki ezeket a hozzárendeléseket, ez alapján töltődnek fel a
 * codeMap és dataMap változók.
 * A code.txt fájl elemeinek módosításával újabb adatokat lehet felvenni a dataMap változóba,
 * így könnyen bővíthetővé válik a szoftver.
 * @warning A szerver és kliens oldalon is meg kell egyezzen a code.txt fájl!
 *
 * A szöveges üzeneteket QSharedPointer-eken kersztül egy várakozási sor tárolja, illetve üzenet érkezésekor a newString()
 * jel kerül kibocsájtásra, mely szintén egy QSharedPointer-en keresztül adja át az üzenetet.
 * Ugyanígy tárolódnak a fogadott adatok is. A tárolási mód megkönnyíti a fájlba mentési folymatot, így biztosan nem veszik el fogadott adat.
*/
class DataParser : public QObject
{
    Q_OBJECT

public:
    /** @brief Konstruktor
     *
     * @param codeFilePath  A code.txt fájl elérési útja.
     */
    DataParser(const QString& codeFilePath);
    /** @brief Visszatér a paraméter stringhez tartozó kóddal.*/
    quint16 getCode(const QString& str){return codeMapInv[str];}
    /** @brief Visszatér a kód-jelentést tároló tárolóval.*/
    const QMap<quint16, QString>& getCodeMap(){return codeMap;}
    /** @brief Visszatér a kód-jelentést tároló tárolóval.*/
    const QMap<QString, double>& getDataMap(){return dataMap;}
    /** @brief Visszatér a szöveges üzenetek várakozási sorával.*/
    QQueue<QSharedPointer<QString>>& getStrQueue(){return strQueue;}
    /** @brief Konzolra írja a dataMap tároló tartalmát.*/
    void PrintDataToDebug();

private:
    /** @brief A kód-jelentést tartalmazó txt fájl objektum.*/
    QFile codeFile;
    /** @brief A kód-jelentést tartalmazó asszociatív tároló.*/
    QMap<quint16, QString> codeMap;
    /** @brief A jelentés-kódot tertalmazó asszociatív tároló.*/
    QMap<QString, quint16> codeMapInv;
    /** @brief Adatokat tartalmazó map, mindíg a legutolsó beérkezett adatot tartalmazza.*/
    QMap<QString, double> dataMap;

    /** @brief A beérkező string üzeneteket tartalmazó várakozásis sor.*/
    QQueue<QSharedPointer<QString>> strQueue;
    /** @brief A beérkező adatokat tartalmazó várakozásis sor.*/
    QQueue<QSharedPointer<QMap<QString, double>>> dataQueue;
    /** @brief A szöveges üzenetek beérkezési idejét tartalmazó várakozásis sor.
     *
     * Az indexek a szöveges üzeneteket tartalmazó várakozási sorok indexeinek megfelelő időponhoz tartonak,
     * vagyis az első üzenethez az első időbélyeg tartozik.
     */
    QQueue<QSharedPointer<QDateTime>> strTimeQueue;
    /** @brief Az adatok beérkezési idejét tartalmazó várakozásis sor.
     *
     * Az indexek az adatokat tartalmazó várakozási sor indexeinek megfelelő időponhoz tartonak,
     * vagyis az első adathoz az első időbélyeg tartozik.
     */
    QQueue<QSharedPointer<QDateTime>> dataTimeQueue;

signals:
    /** @brief Hibakezelő jel.*/
    void errorOccurred(const QString&);
    /** @brief Jelzi, ha új adatot lehet kirajzolni a grafikus felületre.*/
    void newToPlot();
    /** @brief A getQieues slot hatására bocsájtódik ki, átadja az összes várakozási sort.*/
    void giveQueue(QQueue<QSharedPointer<QString>>&, QQueue<QSharedPointer<QMap<QString, double>>>&,
                   QQueue<QSharedPointer<QDateTime>>&, QQueue<QSharedPointer<QDateTime>>&);
    /** @brief Jelzi, ha új szöveges üzenet jött.*/
    void newString(QSharedPointer<QString>);

public slots:
    /** @brief Ide lehet bekötni a kommunikációs dataReady signalokat. @see Communication*/
    void dataInput(QDataStream&);
    /** @brief A paraméterként kapott asszociatív tárolóba bemásolja az akruális adatokat.*/
    void getData(QMap<QString, QVector<double>>&);
    /** @brief Ennek hatására emittálódnak a várakozási sorok.*/
    void getQueues(){emit giveQueue(strQueue, dataQueue, strTimeQueue, dataTimeQueue);}
};

