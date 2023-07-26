#pragma once

#include <QObject>
#include <QGraphicsItem>
#include <QBrush>

/********************* CControlPointItem *******************************/
class CControlPointItem : public QObject, public QGraphicsItem
{
    Q_OBJECT;
    Q_INTERFACES(QGraphicsItem)
public:
    CControlPointItem(QGraphicsItem* parent, QPoint center, int nIndex);
    ~CControlPointItem();

    // 控制点类型
    enum ControlPointType { CP_Rect = 0, CP_Circle };

    // 获得当前控制点在Scene中的坐标
    QPointF                 GetPoint();
    // 设置当前控制点在Scene中的坐标
    void                    SetPoint(QPointF point);

    virtual void            paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;

    virtual QRectF          boundingRect()const override;
    virtual void            mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void            mousePressEvent(QGraphicsSceneMouseEvent *event) override;

protected:
    int                 m_nType;        // 控制点类型
    int                 m_nIndex;       // 控制点的序号
    int                 m_nWidth;       // 控制点宽度
    int                 m_nPenWidth;    // 控制点画笔宽度

    QBrush              m_brush;

    QPointF             m_center;       // 控制点中心坐标
};


