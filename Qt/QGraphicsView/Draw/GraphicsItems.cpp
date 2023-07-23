#include "GraphicsItems.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

#include <QDebug>

CRectItem::CRectItem(QObject *parent)
    : QObject(parent)
{
    this->setAcceptHoverEvents(true);

    m_nWidth = 200;
    m_nHeight = 200;
    m_nVertexWidth = 18;
    m_vecVertex.resize(9);
    GetVertex();
}

CRectItem::~CRectItem()
{
}

void CRectItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{

    painter->setRenderHint(QPainter::Antialiasing, true);

    // Draw rect
    painter->save();

    QPen penRect;
    penRect.setColor(Qt::yellow);
    penRect.setWidth(2);
    painter->setPen(penRect);

    QBrush brushRect;
    QColor colorBrushRect(Qt::green);
    colorBrushRect.setAlpha(20);
    brushRect.setColor(colorBrushRect);
    brushRect.setStyle(Qt::SolidPattern);
    painter->setBrush(brushRect);

    painter->drawRect(QRect(-m_nWidth / 2, -m_nHeight / 2, m_nWidth, m_nHeight));

    painter->restore();

    // Draw vertex
    painter->save();
    QPen penVertex;
    penVertex.setColor(Qt::green);
    penVertex.setWidth(8);
    painter->setPen(penVertex);
    //painter->setBrush(Qt::NoBrush);
    for (int i = 0; i < m_vecVertex.size(); ++i)
    {
        painter->drawRect(m_vecVertex.at(i));
    }

    painter->restore();
}

void CRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{

}

void CRectItem::hoverMoveEvent(QGraphicsSceneHoverEvent * event)
{
    qDebug() << event->pos();
    for (int i = 0; i < m_vecVertex.size(); ++i)
    {
        if ( m_vecVertex.at(i).contains(event->pos()))
        {
            setCursor(QCursor(Qt::SizeAllCursor));
            break;
        }
        else
        {
            setCursor(QCursor(Qt::ArrowCursor));
        }
    }
}

QRectF CRectItem::boundingRect() const
{
    return QRectF(-m_nWidth / 2, -m_nHeight / 2, m_nWidth, m_nHeight);
}

void CRectItem::GetVertex()
{
    int nHalfVertexWidth = m_nVertexWidth / 2;
    int nHalfWidth = m_nWidth / 2;
    int nHalfHeight = m_nHeight / 2;

    m_vecVertex[0] = QRectF(-nHalfWidth - nHalfVertexWidth, -nHalfHeight - nHalfVertexWidth, m_nVertexWidth, m_nVertexWidth);     // Top Left
    m_vecVertex[1] = QRectF(0 - nHalfVertexWidth, -nHalfHeight - nHalfVertexWidth, m_nVertexWidth, m_nVertexWidth);               // Top Middle
    m_vecVertex[2] = QRectF(nHalfWidth - nHalfVertexWidth, -nHalfHeight - nHalfVertexWidth, m_nVertexWidth, m_nVertexWidth);      // Top Right
    m_vecVertex[3] = QRectF(-nHalfWidth-nHalfVertexWidth, -nHalfVertexWidth, m_nVertexWidth, m_nVertexWidth);  // Left
    m_vecVertex[4] = QRectF(-nHalfVertexWidth, -nHalfVertexWidth, m_nVertexWidth, m_nVertexWidth);                              // Center
    m_vecVertex[5] = QRectF(nHalfWidth - nHalfVertexWidth, -nHalfVertexWidth, m_nVertexWidth, m_nVertexWidth);                   // Right
    m_vecVertex[6] = QRectF(-nHalfWidth - nHalfVertexWidth, nHalfHeight - nHalfVertexWidth, m_nVertexWidth, m_nVertexWidth);      // Bottom Left
    m_vecVertex[7] = QRectF(0 - nHalfVertexWidth, nHalfHeight - nHalfVertexWidth, m_nVertexWidth, m_nVertexWidth);                  // Bottom Middle
    m_vecVertex[8] = QRectF(nHalfWidth - nHalfVertexWidth, nHalfHeight - nHalfVertexWidth, m_nVertexWidth, m_nVertexWidth);       // Bottom Right
}
