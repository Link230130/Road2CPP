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
    CControlPointItem(QGraphicsItem* parent, QPoint center);
    ~CControlPointItem();

    // 控制点类型
    enum ControlPointType { CP_Rect = 0, CP_Circle };

    virtual void        paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;

    virtual QRectF      boundingRect()const override;

protected:
    int                 m_nType;        // 控制点类型
    int                 m_nWidth;       // 控制点宽度
    int                 m_nPenWidth;    // 控制点画笔宽度

    QBrush              m_brush;

    QPoint              m_center;       // 控制点中心坐标
};


/********************* CRectItem *******************************/
class CRectItem : public QObject, public  QGraphicsItemGroup
{
    Q_OBJECT;
    Q_INTERFACES(QGraphicsItem)

public:
    CRectItem(QObject *parent);
    ~CRectItem();

    virtual QRectF boundingRect() const override;

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;

    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;

    
private:

    int                             m_nWidth;
    int                             m_nHeight;

    QPoint                          m_center;              // 矩形中心点坐标
    

    int                             m_nVertexWidth;         // 顶点矩形的边长
    QVector<CControlPointItem*>     m_vecControlVertex;     // 1个中心点+4个顶点

    // 初始化顶点坐标
    void InitControlVertex();
};
