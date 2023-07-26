#pragma once

#include <QObject>
#include <QGraphicsItem>
#include <QBrush>

class CControlPointItem;

/********************* CBaseItem *******************************/
#pragma region CBaseItem
class CBaseItem : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    CBaseItem(QObject* parent);
    ~CBaseItem();

    /* 用于更新ItemGroup */
    virtual void    UpdateItemGroup(int nIndex) = 0;

protected:
    // 初始化顶点坐标
    virtual void    InitControlVertex() = 0;

protected:
    QVector<CControlPointItem*>     m_vecControlVertex;     // 控制点列表，1个中心点+4个顶点

};
#pragma endregion

/********************* CRectItem *******************************/
#pragma region CRectItem
class CRectItem : public  CBaseItem
{
    Q_OBJECT;
    Q_INTERFACES(QGraphicsItem)

public:
    CRectItem(QObject *parent);
    ~CRectItem();

    /* 更新控制点位置 */
    virtual void UpdateItemGroup(int nIndex) override;

    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;

protected:
    virtual void InitControlVertex() override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;

private:

    int                             m_nWidth;
    int                             m_nHeight;

    int                             m_nVertexWidth;         // 顶点矩形的边长

    QPoint                          m_center;               // 矩形中心点坐标
    QRectF                          m_boundingRect;         // 外接矩形
};
#pragma endregion