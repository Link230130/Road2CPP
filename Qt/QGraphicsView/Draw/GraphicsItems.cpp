#include "GraphicsItems.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

#include <QDebug>

#include "ControlPointItem.h"

/***************** CBaseItem ********************/
CBaseItem::CBaseItem(QObject * parent)
{
    // 将事件传递到子Item
    this->setHandlesChildEvents(false);
}

CBaseItem::~CBaseItem()
{
}


/***************** CRectItem ********************/
CRectItem::CRectItem(QObject *parent)
    : CBaseItem(parent)
{
    this->setAcceptHoverEvents(true);

    m_nWidth = 300;
    m_nHeight = 200;

    m_center = QPoint(0, 0);

    InitControlVertex();
    m_boundingRect = QRectF(m_vecControlVertex.at(1)->GetPoint(), m_vecControlVertex.at(4)->GetPoint());
}

CRectItem::~CRectItem()
{
}

void CRectItem::InitControlVertex()
{
    m_vecControlVertex.clear();
    m_vecControlVertex.push_back(new CControlPointItem(this, m_center, 0));  // Center
    m_vecControlVertex.push_back(new CControlPointItem(this, m_center - QPoint(m_nWidth / 2, m_nHeight / 2), 1));  // Top left
    m_vecControlVertex.push_back(new CControlPointItem(this, m_center - QPoint(-m_nWidth / 2, m_nHeight / 2), 2)); // Top right
    m_vecControlVertex.push_back(new CControlPointItem(this, m_center - QPoint(m_nWidth / 2, -m_nHeight / 2), 3)); // Bottom left
    m_vecControlVertex.push_back(new CControlPointItem(this, m_center + QPoint(m_nWidth / 2, m_nHeight / 2), 4)); // Bottom right
}

void CRectItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{

    painter->setRenderHint(QPainter::Antialiasing, true);

    // Draw rect
    painter->save();

    painter->setPen(Qt::red);
    QBrush brush;
    brush.setColor(QColor(0, 255, 0, 40));
    brush.setStyle(Qt::SolidPattern);

    painter->setBrush(brush);

    painter->drawRect(m_boundingRect);
    painter->restore();
}

void CRectItem::UpdateItemGroup(int nIndex)
{
    switch (nIndex)
    {
    case 0:
    {
        // Center
        break;
    }
    case 1:
    {
        // Top Left
        break;
    }
    case 2:
    {
        // Top Right
        break;
    }
    case 3:
    {
        // Bottom Left
        break;
    }
    case 4:
    {
        // 根据Bottom Right更新Top Right和Bottom Left
        m_vecControlVertex[2]->SetPoint(QPointF(m_vecControlVertex[4]->x(), m_vecControlVertex[2]->y()));
        m_vecControlVertex[3]->SetPoint(QPointF(m_vecControlVertex[3]->x(), m_vecControlVertex[4]->y()));
        break;
    }
    default:
        break;
    }
    
    m_boundingRect = QRectF(m_vecControlVertex.at(1)->GetPoint(), m_vecControlVertex.at(4)->GetPoint());
    this->update();
}

QRectF CRectItem::boundingRect() const
{
    return m_boundingRect;
}

QPainterPath CRectItem::shape() const
{
    QPainterPath path;
    path.addRect(m_boundingRect);
    return path;
}
