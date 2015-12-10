#include "QMLData.h"

QMLData::QMLData(double data, QObject *parent) : QObject(parent), storedData(data)
{

}

void QMLData::setData(const double& d)
{
    if(d != storedData)
    {
        storedData = d;
        emit dataChanged();
    }
}

QMLData& QMLData::operator = (const QMLData& other)
{
    this->storedData = other.storedData;
    return *this;
}
