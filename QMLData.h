#pragma once

#include <QObject>
#include <QDebug>

/** @brief A QML felület és a C++ kód közötti kommunikációt megkönnyítő objektum.
 *
 * Ezek az objektumok egy double értéket tudnak tárolni. Minden lehetséges adathoz létrehozunk
 * egy ilyen objektumot, majd beregisztráljuk a QML rendszerbe. Így a QML felületről elérgetővé válnak
 * az objektum függvényei, signaljai.
 * Ha az objektumban tárolt adat megváltozik, a dataChanged() signal emittálásra kerül,
 * a QML felületen frissül az adat.
*/
class QMLData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double data READ data WRITE setData NOTIFY dataChanged)

public:
    /** @brief Konstrukor.
     *
     * @param data  Inicializáló adat, alapértelmezetten 0.
    */
    QMLData(double data = 0, QObject *parent = 0);
    /** @brief Copy konstruktor.
     *
     * Az egyenlőség operátort használja fel, gyakorlatilag lemásolja az adatot.
    */
    QMLData(const QMLData& other):QObject(){this->storedData = other.storedData;}
    /** @brief Adat módosító függvény.
     *
     * A paraméterként kapott értéket bemásolja a tárolt adat változóba, majd a dataChanger() jelet bocsájtja ki.
    */
    void setData(const double&);
    /** @brief Adat olvasása.
     *
     *  @returns Visszatér a tárold adattal.
    */
    double data() const {return storedData;}
    /** @brief Egyenlőség operátor.
     *
     * Megkönnyíti az objektumok másolását.
    */
    QMLData& operator = (const QMLData&);

private:
    /** @brief Ebben a változóban tárolódik az adat.*/
    double storedData;

signals:
    /** @brief Kibocsájtódik, ha megváltozott az adat értéke.*/
    void dataChanged();
};
