#ifndef DATALOGGER_H
#define DATALOGGER_H

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

class DataLogger : public QObject
{
    Q_OBJECT
public:
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

#endif // DATALOGGER_H
