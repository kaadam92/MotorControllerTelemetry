#pragma once

#include <QtQuick>
#include <QDebug>

class QCustomPlot;

/** @brief A grafikont tartalmazó és kezelését megvalósító objektum.
 *
 * A
 */
class CustomPlotItem : public QQuickPaintedItem
{
    Q_OBJECT

public:
    CustomPlotItem( QQuickItem* parent = 0 );
    virtual ~CustomPlotItem();

    void paint( QPainter* painter );

    Q_INVOKABLE void initCustomPlot();

    QCustomPlot* getPtr(){return m_CustomPlot;}

protected:
    void routeMouseEvents( QMouseEvent* event );

    virtual void mousePressEvent( QMouseEvent* event );
    virtual void mouseReleaseEvent( QMouseEvent* event );
    virtual void mouseMoveEvent( QMouseEvent* event );
    virtual void mouseDoubleClickEvent( QMouseEvent* event );

    void setup( QCustomPlot* customPlot );

private:
    QCustomPlot* m_CustomPlot;

private slots:
    void onCustomReplot();
    void updateCustomPlotSize();
};
