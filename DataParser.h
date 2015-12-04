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
    quint16 getCode(const QString& str){return codeMapInv[str];}

private:
    /** A kód-jelentést tartalmazó txt fájl objektum.*/
    QFile codeFile;
    /** A kód-jelentést tartalmazó asszociatív tároló.*/
    QMap<quint16, QString> codeMap;
    QMap<QString, quint16> codeMapInv;
    /** Adatokat tartalmazó map, két időegység között folyamatosan töltődik fel adattal.*/
    QMap<QString, double> dataMap;


signals:
    void errorOccurred(const QString&);
    /** Jelzi, ha új adatot lehet kirajzolni a grafikus felületre.*/
    void newToPlot();

public slots:
    /** Ide lehet bekötni a kommunikációs dataReady signalokat.*/
    void dataInput(QDataStream&);
    /** A paraméterként kapott asszociatív tárolóba bemásolja az akruális adatokat.*/
    void getData(QMap<QString, QVector<double>>&);
};

