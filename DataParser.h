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

class DataParser : public QObject
{
    Q_OBJECT

public:
    DataParser(const QString&);

    void PrintDataToDebug();

private:
    /** A kód-jelentést tartalmazó txt fájl objektum.*/
    QFile codeFile;
    /** A kód-jelentést tartalmazó asszociatív tároló.*/
    QMap<QString, quint16> codeMap;
    /** Adatokat tartalmazó map, két időegység között folyamatosan töltődik fel adattal.*/
    QMap<quint16, double> dataMap;

    /** */
    QQueue<QDateTime> timestampQueue;
    QQueue<QMap<quint16, double>> dataQueue;
signals:
    void errorOccurred(const QString&);

public slots:
    /** Ide lehet bekötni a kommunikációs dataReady signalokat.*/
    void dataInput(QDataStream&);

    /** Ide lehet bekötni a timer signalt. Minden egyes híváskor
     * elmenti új timestampel az adatokat dataTimestamp-be.*/
    void saveDataTimestamp();

};

