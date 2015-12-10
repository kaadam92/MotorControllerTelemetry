#include "DataLogger.h"

const uint loggerTimerInterval = 1000;
const char dateTimeFormat[] = "yyyy.MM.dd. hh:mm:ss";

DataLogger::~DataLogger()
{
    logFile.flush();
    logFile.close();
    strLogFile.flush();
    strLogFile.close();
}

DataLogger::DataLogger(const QString& logFilePath, const QString& logFileStylePath, const QString& strLogFilePath)
    : logFile(logFilePath), logFileStyle(logFileStylePath), strLogFile(strLogFilePath)
{
    /** A fájlnevet megtoldom az aktuális időbélyeggel, így egyedi lesz a fájlnév.*/
    QStringList pathList = logFilePath.split('.');
    logFile.setFileName(pathList[0]+QDateTime::currentDateTime().toString("_yyyy_MM_dd_hh_mm_ss")+'.'+pathList[1]);
    pathList = strLogFilePath.split('.');
    strLogFile.setFileName(pathList[0]+QDateTime::currentDateTime().toString("_yyyy_MM_dd_hh_mm_ss")+'.'+pathList[1]);

    printLogFileHeader();

    QObject::connect(&loggerTimer, SIGNAL(timeout()),
                     this, SLOT(loggerTimerTimeout()));
    loggerTimer.setInterval(loggerTimerInterval);
    loggerTimer.start();
}

void DataLogger::printLogFileHeader()
{
    if(!logFile.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        emit errorOccurred(QString("A log fájlt nem lehet megnyitni."));
        qWarning() << "A log fájlt nem lehet megnyitni." << endl;
        return;
    }
    if(!logFileStyle.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        emit errorOccurred(QString("A logStyle fájlt nem lehet megnyitni."));
        qWarning() << "A logStyle fájlt nem lehet megnyitni." << endl;
        logFile.close();
        return;
    }
    QTextStream logFileStream(&logFile);
    QTextStream logFileStyleStream(&logFileStyle);
    /** A stílus fájl tartalmazza a log file fejlécét.
     * Ezt bemásolom a logfájl elejére.*/
    QString line;
    line = logFileStyleStream.readLine();
    if(line.isNull())
    {
        emit errorOccurred(QString("HIBA a stílus fájl üres."));
        qWarning() << "HIBA a stílus fájl üres.";
        return;
    }
    logFileStream << line << endl;
    /** A stílus alapján kitöltöm a printOrder vektort,
     * így később is meg lesz a sorrend.*/
    QStringList dataNameList;
    dataNameList = line.split(',');
    QStringList::iterator i;
    for(i = dataNameList.begin(); i != dataNameList.end(); i++)
    {
        printOrder.append(*i);
    }

    logFile.close();
    logFileStyle.close();
}

void DataLogger::saveToLog(QQueue<QSharedPointer<QString>>& strQueue, QQueue<QSharedPointer<QMap<QString, double>>>& dataQueue,
                           QQueue<QSharedPointer<QDateTime>>& strTimeQueue, QQueue<QSharedPointer<QDateTime>>& dataTimeQueue)
{
    if(!logFile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append))
    {
        emit errorOccurred(QString("A log fájlt nem lehet megnyitni."));
        qWarning() << "A log fájlt nem lehet megnyitni." << endl;
        return;
    }
    if(!strLogFile.open(QIODevice::ReadWrite | QIODevice::Text| QIODevice::Append))
    {
        emit errorOccurred(QString("Az strLog fájlt nem lehet megnyitni."));
        qWarning() << "Az strLog fájlt nem lehet megnyitni." << endl;
        return;
    }

    QTextStream logFileStream(&logFile);
    QTextStream strLogFileStream(&strLogFile);
    while(!strQueue.isEmpty())
    {
        QSharedPointer<QDateTime> timePtr = strTimeQueue.dequeue();
        QSharedPointer<QString> strPtr = strQueue.dequeue();

        qDebug() << *strPtr;
        strLogFileStream << timePtr->toString(dateTimeFormat) << "\t" << *(strPtr) << endl;
        timePtr.clear();
        strPtr.clear();
    }
    while(!dataQueue.isEmpty())
    {
        QSharedPointer<QDateTime> timePtr = dataTimeQueue.dequeue();
        logFileStream << timePtr->toString(dateTimeFormat);

        QSharedPointer<QMap<QString, double>> dataPtr = dataQueue.dequeue();
        QVector<QString>::iterator i;
        i = printOrder.begin();
        for(++i; i != printOrder.end(); ++i)
        {
            logFileStream << ',' << (*dataPtr)[*i];
        }
        logFileStream << endl;
        timePtr.clear();
        dataPtr.clear();
    }

    logFile.close();
    strLogFile.close();
}
