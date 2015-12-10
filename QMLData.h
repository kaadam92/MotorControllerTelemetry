#pragma once
#include <QObject>
#include <QDebug>

class QMLData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double data READ data WRITE setData NOTIFY dataChanged)
public:
    QMLData(double data = 0, QObject *parent = 0);
    QMLData(const QMLData& other){this->storedData = other.storedData;}
    void setData(const double&);
    double data() const {return storedData;}

    QMLData& operator = (const QMLData&);

private:
    double storedData;

signals:
    void dataChanged();
};
