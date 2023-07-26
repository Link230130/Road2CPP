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

    // ���Ƶ�����
    enum ControlPointType { CP_Rect = 0, CP_Circle };

    // ��õ�ǰ���Ƶ���Scene�е�����
    QPointF                 GetPoint();
    // ���õ�ǰ���Ƶ���Scene�е�����
    void                    SetPoint(QPointF point);

    virtual void            paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;

    virtual QRectF          boundingRect()const override;
    virtual void            mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void            mousePressEvent(QGraphicsSceneMouseEvent *event) override;

protected:
    int                 m_nType;        // ���Ƶ�����
    int                 m_nIndex;       // ���Ƶ�����
    int                 m_nWidth;       // ���Ƶ���
    int                 m_nPenWidth;    // ���Ƶ㻭�ʿ��

    QBrush              m_brush;

    QPointF             m_center;       // ���Ƶ���������
};


