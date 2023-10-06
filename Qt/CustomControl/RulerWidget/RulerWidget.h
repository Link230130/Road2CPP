/*
* ����һ���Զ���Ŀ̶ȳ߿ؼ�
*/

#pragma once

#include <QWidget>

enum class RulerUnit {
    NM = 0, // ����
    UM,     // ΢��
    MM,     // ����
    CM,     // ����
    M,      // ��
    KM      // ǧ��
};

class RulerWidget : public QWidget
{
    Q_OBJECT

public:
    RulerWidget(QWidget *parent = nullptr);
    ~RulerWidget();

protected:
    virtual void    paintEvent(QPaintEvent *event) override;
    virtual void    wheelEvent(QWheelEvent *event) override;

    virtual void    DrawHorizontalRuler(QPainter* painter, QPen* pen);
    virtual void    DrawVerticalRuler(QPainter* painter, QPen* pen);

    void            SetUnit(RulerUnit unit);

protected:
    // �����̶�֮������ؼ�������ڴ��ڻ���
    int             m_nIntervalPixel;

    // �̶ȳߵľ��ȣ��������̶�֮���ʾ�������ȣ���10����ľ��Ǿ���Ϊ10��m_unit
    int             m_nAccuracy;

    // 1�����������ȵ�ת����ϵ����1000������Ҫ��ʾ�ĳ���Ϊ10000΢�ף���m_fConvert=10000΢��/1000����=10΢��/����
    float           m_fConvert;

    // �̶ȳߵ�����ϵ��
    //float           m_fZoom;    // �����ø��������㣬����־�������
    int             m_nZoomFactor;

    // �̶ȳ߱�ʾ������λ��Ĭ���Ǻ���
    RulerUnit       m_unit;
    // �̶ȳߵ�λ�� nm/um/mm/cm/m/km ��
    QString         m_strRulerUnit;

    // �̶ȵ����ͣ�ˮƽ�̶ȳߺʹ�ֱ�̶ȳߣ�Ĭ����ˮƽ�̶ȳ�
    Qt::Orientation m_orientation;

    // �̶ȳ�0�����������
    QPointF         m_pointZero;
};
