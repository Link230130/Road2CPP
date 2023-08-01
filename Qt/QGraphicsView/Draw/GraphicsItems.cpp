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
    qDebug() << "paint, center point=" << mapToScene(m_vecControlVertex[0]->GetPoint()) << m_vecControlVertex[0]->GetPoint();

    painter->setRenderHint(QPainter::Antialiasing, true);

    // Draw rect
    painter->save();

    painter->setPen(Qt::red);
    QBrush brush;
    brush.setColor(QColor(0, 255, 0, 40));
    brush.setStyle(Qt::SolidPattern);

    painter->setBrush(brush);

    painter->drawRect(m_boundingRect);
#if 0
    // 测试中心点
    painter->setPen(Qt::red);
    painter->drawEllipse(m_vecControlVertex[0]->GetPoint(), 15, 15);
#endif
    painter->restore();
}

void CRectItem::UpdateItemGroup(int nIndex)
{
    switch (nIndex)
    {
    case 1:
    {
        // Top Left
        m_vecControlVertex[2]->SetPoint(QPointF(m_vecControlVertex[2]->x(), m_vecControlVertex[1]->y()));
        m_vecControlVertex[3]->SetPoint(QPointF(m_vecControlVertex[1]->x(), m_vecControlVertex[3]->y()));
        break;
    }
    case 2:
    {
        // Top Right
        m_vecControlVertex[1]->SetPoint(QPointF(m_vecControlVertex[1]->x(), m_vecControlVertex[2]->y()));
        m_vecControlVertex[4]->SetPoint(QPointF(m_vecControlVertex[2]->x(), m_vecControlVertex[4]->y()));
        break;
    }
    case 3:
    {
        // Bottom Left
        m_vecControlVertex[1]->SetPoint(QPointF(m_vecControlVertex[3]->x(), m_vecControlVertex[1]->y()));
        m_vecControlVertex[4]->SetPoint(QPointF(m_vecControlVertex[4]->x(), m_vecControlVertex[3]->y()));
        break;
    }
    case 4:
    {
        // 根据Bottom Right更新Top Right和Bottom Left
        m_vecControlVertex[0]->SetPoint(mapFromParent(QPointF(0, 0)));
        m_vecControlVertex[2]->SetPoint(QPointF(m_vecControlVertex[4]->x(), m_vecControlVertex[2]->y()));
        m_vecControlVertex[3]->SetPoint(QPointF(m_vecControlVertex[3]->x(), m_vecControlVertex[4]->y()));
        break;
    }
    default:
        break;
    }
    this->prepareGeometryChange();
    // 更新中心点
    m_vecControlVertex[0]->SetPoint(QPointF((m_vecControlVertex.at(1)->x() + m_vecControlVertex.at(4)->x()) / 2,
        (m_vecControlVertex.at(1)->y() + m_vecControlVertex.at(4)->y()) / 2));

    QPointF topLeftPoint = m_vecControlVertex.at(1)->GetPoint();
    QPointF bottomRightPoint = m_vecControlVertex.at(4)->GetPoint();

    if (topLeftPoint.x() > bottomRightPoint.x() || topLeftPoint.y() > bottomRightPoint.y())
    {
        m_boundingRect = QRectF(bottomRightPoint, topLeftPoint);
    }
    else
    {
        m_boundingRect = QRectF(topLeftPoint, bottomRightPoint);
    }
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
