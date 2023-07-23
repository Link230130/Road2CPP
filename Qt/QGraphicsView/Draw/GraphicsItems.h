#pragma once

#include <QObject>
#include <QGraphicsItem>

class CRectItem : public QObject, public QGraphicsItem
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
    int             m_nWidth;
    int             m_nHeight;
    
    int             m_nVertexWidth;     // 顶点矩形的边长

    QVector<QRectF>   m_vecVertex;    // 9个顶点

    void GetVertex();
};
