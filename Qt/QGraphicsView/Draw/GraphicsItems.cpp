#include "GraphicsItems.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

#include <QDebug>

CControlPointItem::CControlPointItem(QGraphicsItem* parent, QPoint center)
    :QGraphicsItem(parent)
{
    m_center = center;
    m_nType = CP_Rect;
    m_nWidth = 8;
    m_nPenWidth = 2;
    m_brush.setColor(Qt::yellow);
    m_brush.setStyle(Qt::SolidPattern);

    this->setPos(center);
}

CControlPointItem::~CControlPointItem()
{
}

void CControlPointItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    painter->setRenderHint(QPainter::Antialiasing, true);

    painter->save();

    QPen pen;
    pen.setColor(Qt::green);
    pen.setWidth(m_nPenWidth);
    painter->setPen(pen);
    painter->setBrush(Qt::green);
    painter->drawRect(-m_nWidth / 2, -m_nWidth / 2, m_nWidth, m_nWidth);

    painter->restore();
}

QRectF CControlPointItem::boundingRect() const
{
    return QRectF(-m_nWidth / 2, -m_nWidth / 2, m_nWidth, m_nWidth);
}


/***************** CRectItem ********************/
CRectItem::CRectItem(QObject *parent)
    : QObject(parent)
{
    this->setAcceptHoverEvents(true);

    m_nWidth = 300;
    m_nHeight = 200;

    m_center = QPoint(0, 0);

    InitControlVertex();
}

CRectItem::~CRectItem()
{
}

void CRectItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{

    painter->setRenderHint(QPainter::Antialiasing, true);

    // Draw rect
    painter->save();

    QPainterPath rectPath;
    rectPath.addRect(m_vecControlVertex.at(1)->boundingRect());
    rectPath.addRect(m_vecControlVertex.at(4)->boundingRect());

    painter->setPen(Qt::red);
    QBrush brush;
    brush.setColor(QColor(0, 255, 0, 40));
    brush.setStyle(Qt::SolidPattern);

    painter->setBrush(brush);

    painter->drawRect(-m_nWidth / 2, -m_nHeight / 2, m_nWidth, m_nHeight);
    painter->restore();
}

void CRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{

}

void CRectItem::hoverMoveEvent(QGraphicsSceneHoverEvent * event)
{

}

void CRectItem::InitControlVertex()
{
    m_vecControlVertex.clear();
    m_vecControlVertex.push_back(new CControlPointItem(this, m_center));  // Center
    m_vecControlVertex.push_back(new CControlPointItem(this, m_center - QPoint(m_nWidth / 2, m_nHeight / 2)));  // Top left
    m_vecControlVertex.push_back(new CControlPointItem(this, m_center - QPoint(-m_nWidth / 2, m_nHeight / 2))); // Top right
    m_vecControlVertex.push_back(new CControlPointItem(this, m_center - QPoint(m_nWidth / 2, -m_nHeight / 2))); // Bottom left
    m_vecControlVertex.push_back(new CControlPointItem(this, m_center + QPoint(m_nWidth / 2, m_nHeight / 2))); // Bottom right
}

QRectF CRectItem::boundingRect() const
{
    return QRectF(-m_nWidth / 2, -m_nHeight / 2, m_nWidth, m_nHeight);
}



