#pragma once

#include <QtQuick>
#include <QDebug>

class QCustomPlot;

/** @brief A grafikont tartalmazó és kezelését megvalósító objektum.
 *
 * Tartalmazza az inicializálást, a különféle események kezelését.
 */
class CustomPlotItem : public QQuickPaintedItem
{
    Q_OBJECT

public:
    /** @brief Konstuktor.
     *
     * A megfelelő jeleket közi össze, jelzi, hogy már kétezik.
     */
    CustomPlotItem( QQuickItem* parent = 0 );
    virtual ~CustomPlotItem();
    /** @brief QML felületről hívható inicializáló.*/
    Q_INVOKABLE void initCustomPlot();
    /** @brief Kirajzolja a felületet.*/
    void paint( QPainter* painter );
    /** @brief Visszatér a grafikon muatatójával. @see Application*/
    QCustomPlot* getPtr(){return m_CustomPlot;}

protected:
    void routeMouseEvents( QMouseEvent* event );

    virtual void mousePressEvent( QMouseEvent* event );
    virtual void mouseReleaseEvent( QMouseEvent* event );
    virtual void mouseMoveEvent( QMouseEvent* event );
    virtual void mouseDoubleClickEvent( QMouseEvent* event );

    /** @brief Inicializálja a grafikont.*/
    void setup( QCustomPlot* customPlot );

private:
    /** @brief A grafikonra mutató pointer.*/
    QCustomPlot* m_CustomPlot;

private slots:
    /** @brief Újrarajzolja a grafikont.*/
    void onCustomReplot();
    /** @brief Módosítja a grafikon méreteit.*/
    void updateCustomPlotSize();
};
