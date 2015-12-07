#include "DataParser.h"

const quint8 cellnum_def = 12;

DataParser::DataParser (const QString& codeFilePath)
    :codeFile(codeFilePath)
{
    /** Hibát jelez, ha nem sikerült a fájlt megnyitni. */
    if(!codeFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        emit errorOccurred(QString("Can't open codeMap file."));
        qWarning() << "HIBA a fájl nem található." << endl;
        return;
    }
    QTextStream fileInput(&codeFile);
    QStringList list;
    QString line;
    bool ok;

    /** Feltölti a codeMap változót a fájlban található értékekkel. */
    line = fileInput.readLine();
    while(!line.isNull())
    {
        list = line.split("-");
        codeMap.insert(list.at(0).toInt(&ok, 16), list.at(1));
        codeMapInv.insert(list.at(1), list.at(0).toInt(&ok, 16));
        line = fileInput.readLine();
    }

    /** A fájlból való betöltés alapján a dataMap inicializációja 0-val.*/
    QMapIterator<quint16, QString> i(codeMap);
    while (i.hasNext())
    {
        i.next();
        dataMap[i.value()]=0;
    }
}

void DataParser::dataInput(QDataStream& stream)
{
    //qDebug() << "Adat érkezett"<< endl;

    QMap<QString, double> tmpData = dataMap;

    QByteArray byteArray;
    stream >> byteArray;

    quint16 code;
    double value;
    uint i=1;
    uint k=(sizeof(quint16) + sizeof(double));

    if(byteArray.size() >= k)
    {
        /** Első kód kinyerése. Ettől függ a további műveletek sorrendje.*/
        memcpy(&code, byteArray.data(), sizeof(quint16));
        /** String érkezett. Ekkor csak a string érkezhet meg, más adatot nem tartalmaz a tömb.*/
        if(code==codeMapInv["str"])
        {
            QString str;
            /** A string a két bájtos kód után található.*/
            str = (byteArray.data() + sizeof(quint16));
            /** A stringre shared pointert készítek, hogy kívülről elérhető legyen és
             * a használat után meg is szűnjön.*/
            QSharedPointer<QString> strPtr = QSharedPointer<QString>::create(str);
            QSharedPointer<QDateTime> timePtr = QSharedPointer<QDateTime>::create(QDateTime::currentDateTime());
            strQueue.enqueue(strPtr);
            strTimeQueue.enqueue(timePtr);
        }
        else if(code==codeMapInv["vcells"])
        {
            i = 1;
            k = sizeof(double);
            QString strcode("cell");
            while(byteArray.size() >= sizeof(quint16) + i*sizeof(double))
            {
                memcpy(&value, byteArray.data() + sizeof(quint16) + (i-1)*sizeof(double), sizeof(double));
                tmpData[strcode.append(QString::number(i))]=value;
                i++;
            }

            dataMap = tmpData;
            QSharedPointer<QMap<QString, double>> dataPtr = QSharedPointer<QMap<QString, double>>::create(tmpData);
            QSharedPointer<QDateTime> timePtr = QSharedPointer<QDateTime>::create(QDateTime::currentDateTime());
            dataQueue.enqueue(dataPtr);
            dataTimeQueue.enqueue(timePtr);
        }
        else
        {
            while(byteArray.size() >= i*k)
            {
                memcpy(&code, byteArray.data() + (i-1)*k, sizeof(quint16));
                memcpy(&value, byteArray.data() + sizeof(quint16) + (i-1)*k, sizeof(double));
                tmpData[codeMap.value(code)]=value;
                i++;
            }
            dataMap = tmpData;
            QSharedPointer<QMap<QString, double>> dataPtr = QSharedPointer<QMap<QString, double>>::create(tmpData);
            QSharedPointer<QDateTime> timePtr = QSharedPointer<QDateTime>::create(QDateTime::currentDateTime());
            dataQueue.enqueue(dataPtr);
            dataTimeQueue.enqueue(timePtr);
        }
    }
    //PrintDataToDebug();
}

void DataParser::getData(QMap<QString, QVector<double>>& cont)
{
    QMap<QString, double>::iterator idata;

    for (idata=dataMap.begin(); idata!=dataMap.end(); ++idata)
    {
        cont[idata.key()].append(idata.value());
    }

    emit newToPlot();
}

// Test for master branch

void DataParser::PrintDataToDebug()
{
    QMapIterator<QString, double> i(dataMap);
    while (i.hasNext())
    {
        i.next();
        qDebug() << i.key() << ": " << i.value() << endl;
    }
}
