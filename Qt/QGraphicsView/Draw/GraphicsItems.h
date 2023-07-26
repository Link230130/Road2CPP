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

    /* ���ڸ���ItemGroup */
    virtual void    UpdateItemGroup(int nIndex) = 0;

protected:
    // ��ʼ����������
    virtual void    InitControlVertex() = 0;

protected:
    QVector<CControlPointItem*>     m_vecControlVertex;     // ���Ƶ��б�1�����ĵ�+4������

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

    /* ���¿��Ƶ�λ�� */
    virtual void UpdateItemGroup(int nIndex) override;

    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;

protected:
    virtual void InitControlVertex() override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;

private:

    int                             m_nWidth;
    int                             m_nHeight;

    int                             m_nVertexWidth;         // ������εı߳�

    QPoint                          m_center;               // �������ĵ�����
    QRectF                          m_boundingRect;         // ��Ӿ���
};
#pragma endregion