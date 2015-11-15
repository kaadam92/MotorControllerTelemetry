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
    QMap<QString, qint16> codeMap;

    /** 2D map data container. */
    QMap<QDateTime, QMap<qint16, double>> data;

signals:
    void errorOccurred(const QString&);

public slots:
    /** Ide lehet bekötni a kommunikációs dataReady signalokat.*/
    void dataInput(QDataStream&);

};

