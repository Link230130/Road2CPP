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

    // ���Ƶ�����
    enum ControlPointType { CP_Rect = 0, CP_Circle };

    virtual void        paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;

    virtual QRectF      boundingRect()const override;

protected:
    int                 m_nType;        // ���Ƶ�����
    int                 m_nWidth;       // ���Ƶ���
    int                 m_nPenWidth;    // ���Ƶ㻭�ʿ��

    QBrush              m_brush;

    QPoint              m_center;       // ���Ƶ���������
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

    QPoint                          m_center;              // �������ĵ�����
    

    int                             m_nVertexWidth;         // ������εı߳�
    QVector<CControlPointItem*>     m_vecControlVertex;     // 1�����ĵ�+4������

    // ��ʼ����������
    void InitControlVertex();
};
