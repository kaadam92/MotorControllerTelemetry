#pragma once

#include <QtQuick>
#include <QMap>
#include <QVector>
#include <QDateTime>
#include <QTimer>
#include <QDebug>

class QCustomPlot;

class CustomPlotItem : public QQuickPaintedItem
{
    Q_OBJECT

public:
    CustomPlotItem( QQuickItem* parent = 0 );
    virtual ~CustomPlotItem();

    void paint( QPainter* painter );

    void SayBMEG(){qDebug() << "BMEG";}

    Q_INVOKABLE void initCustomPlot();

protected:
    void routeMouseEvents( QMouseEvent* event );

    virtual void mousePressEvent( QMouseEvent* event );
    virtual void mouseReleaseEvent( QMouseEvent* event );
    virtual void mouseMoveEvent( QMouseEvent* event );
    virtual void mouseDoubleClickEvent( QMouseEvent* event );

    void setupQuadraticDemo( QCustomPlot* customPlot );

private:
    QCustomPlot*         m_CustomPlot;

    /** A grafikonra rajzolandó adatokat tartalmazó asszociatív tároló.*/
    QMap<QString, QVector<double>> dataVectorMap;
    /** A grafikon időtengelyét leképező vektor.*/
    QVector<QDateTime> timeVec;
    /** Új adatok beolvasásához és újrarajzoláshoz használt timer.*/
    QTimer replotTimer;

signals:
    /** Hatására meg kell történjen az új adatok betöltése a paraméterként
     * átadott asszociatív tárolóban.*/
    void getData(QMap<QString, QVector<double>>&);

public slots:
    /** Hatására emittálódik a getData(...) signal.*/
    void replotTimeout(){emit getData(dataVectorMap);}
    /** Hatására az adatoknak megfelelően újrarajzolódik a grafikon.
     * Új adatok felvétele után ajánlott használni.*/
    void replot();

private slots:
    //void graphClicked( QCPAbstractPlottable* plottable );
    void onCustomReplot();
    void updateCustomPlotSize();
};
