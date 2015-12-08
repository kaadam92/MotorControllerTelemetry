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
    uint readBytes = 0;

    if(byteArray.size() >= sizeof(quint16))
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
        /** Más esetben adat jött.*/
        else
        {
            while(byteArray.size() >= readBytes)
            {
                memcpy(&code, byteArray.data() + readBytes, sizeof(quint16));
                readBytes += sizeof(quint16);
                /** Ha a cellafeszültségek jönnek, más eljárásra van szükség:
                 *  a kód után a cellafeszültségek jönnek sorban.*/
                if(code == codeMapInv["vcells"])
                {
                    uint vcellByte = readBytes;
                    uint cellnum = 1;
                    QString strcode("cell");
                    while(cellnum_def*sizeof(double) > readBytes-vcellByte)
                    {
                        memcpy(&value, byteArray.data() + readBytes, sizeof(double));
                        readBytes += sizeof(double);
                        tmpData[strcode+QString::number(cellnum)]=value;
                        cellnum++;
                    }
                }
                /** Egyébként sima adat jön: double érték.*/
                else
                {
                    memcpy(&value, byteArray.data() + readBytes, sizeof(double));
                    readBytes += sizeof(double);
                    tmpData[codeMap.value(code)]=value;
                }
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
