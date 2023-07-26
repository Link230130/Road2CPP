#include "ControlPointItem.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include "GraphicsItems.h"


CControlPointItem::CControlPointItem(QGraphicsItem* parent, QPoint center, int nIndex)
    :QGraphicsItem(parent)
{
    m_center = center;
    m_nType = CP_Rect;
    m_nIndex = nIndex;
    m_nWidth = 8;
    m_nPenWidth = 2;
    m_brush.setColor(Qt::yellow);
    m_brush.setStyle(Qt::SolidPattern);

    this->setPos(center);
}

CControlPointItem::~CControlPointItem()
{
}

QPointF CControlPointItem::GetPoint()
{
    return m_center;
}

void CControlPointItem::SetPoint(QPointF point)
{
    m_center = point;
    this->setPos(m_center);
    return;
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

void CControlPointItem::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
    // 偏移量
    const QPointF pointDiff = event->scenePos() - event->lastScenePos();

    QPointF newCenter = m_center + pointDiff;

    // 更新控制点在parant中的位置
    SetPoint(newCenter);

    CBaseItem* pParantItem = dynamic_cast<CBaseItem*>(this->parentItem());
    if (pParantItem == nullptr)
    {
        return;
    }
    pParantItem->UpdateItemGroup(m_nIndex);
    qDebug() << "Control Point Index=" << m_nIndex << ",pointDiff=" << pointDiff;
}
void CControlPointItem::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    //qDebug() << "control index = " << m_nIndex << ",pressed";
}

