#include "CustomPlotItem.h"
#include "QCustomPlot/qcustomplot.h"
#include <QDebug>

CustomPlotItem::CustomPlotItem( QQuickItem* parent ) : QQuickPaintedItem( parent )
    , m_CustomPlot( nullptr )
{
    setFlag( QQuickItem::ItemHasContents, true );
    setAcceptedMouseButtons( Qt::AllButtons );

    connect( this, &QQuickPaintedItem::widthChanged, this, &CustomPlotItem::updateCustomPlotSize );
    connect( this, &QQuickPaintedItem::heightChanged, this, &CustomPlotItem::updateCustomPlotSize );

}

CustomPlotItem::~CustomPlotItem()
{
    delete m_CustomPlot;
    m_CustomPlot = nullptr;
}

void CustomPlotItem::initCustomPlot()
{
    m_CustomPlot = new QCustomPlot();

    updateCustomPlotSize();

    setup( m_CustomPlot );

    connect( m_CustomPlot, &QCustomPlot::afterReplot, this, &CustomPlotItem::onCustomReplot );

    m_CustomPlot->replot();
}


void CustomPlotItem::paint( QPainter* painter )
{
    if (m_CustomPlot)
    {
        QPixmap    picture( boundingRect().size().toSize() );
        QCPPainter qcpPainter( &picture );

        //m_CustomPlot->replot();
        m_CustomPlot->toPainter( &qcpPainter );

        painter->drawPixmap( QPoint(), picture );
    }
}

void CustomPlotItem::mousePressEvent( QMouseEvent* event )
{
    qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void CustomPlotItem::mouseReleaseEvent( QMouseEvent* event )
{
    qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void CustomPlotItem::mouseMoveEvent( QMouseEvent* event )
{
    routeMouseEvents( event );
}

void CustomPlotItem::mouseDoubleClickEvent( QMouseEvent* event )
{
    qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void CustomPlotItem::routeMouseEvents( QMouseEvent* event )
{
    if (m_CustomPlot)
    {
        QMouseEvent* newEvent = new QMouseEvent( event->type(), event->localPos(), event->button(), event->buttons(), event->modifiers() );
        QCoreApplication::postEvent( m_CustomPlot, newEvent );
    }
}

void CustomPlotItem::updateCustomPlotSize()
{
    if (m_CustomPlot)
    {
        m_CustomPlot->setGeometry( 0, 0, width(), height() );
    }
}

void CustomPlotItem::onCustomReplot()
{
    update();
}

void CustomPlotItem::setup( QCustomPlot* customPlot )
{
    customPlot->addGraph();
    customPlot->graph( 0 )->setPen( QPen( Qt::red ) );
    customPlot->graph( 0 )->setSelectedPen( QPen( Qt::blue, 2 ) );
    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setDateTimeFormat("yyyy.MM.dd.\nhh:mm:ss:zzz");

    customPlot->addGraph();
    customPlot->graph( 1 )->setPen( QPen( Qt::magenta ) );
    customPlot->graph( 1 )->setSelectedPen( QPen( Qt::blue, 2 ) );
    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setDateTimeFormat("yyyy.MM.dd.\nhh:mm:ss:zzz");

    customPlot->xAxis->setLabel( "t" );
    customPlot->yAxis->setLabel( "y" );

    customPlot->xAxis->setRange( -1, 1 );
    customPlot->yAxis->setRange( -20, 50 );

    customPlot ->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iMultiSelect );
    connect( customPlot, SIGNAL( plottableClick( QCPAbstractPlottable*, QMouseEvent* ) ), this, SLOT( graphClicked( QCPAbstractPlottable* ) ) );
}
