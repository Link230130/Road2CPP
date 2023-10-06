/*
* 这是一个自定义的刻度尺控件
*/

#pragma once

#include <QWidget>

enum class RulerUnit {
    NM = 0, // 纳米
    UM,     // 微米
    MM,     // 毫米
    CM,     // 厘米
    M,      // 米
    KM      // 千米
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
    // 两个刻度之间的像素间隔，用于窗口绘制
    int             m_nIntervalPixel;

    // 刻度尺的精度，即两个刻度之间表示的物理长度；如10代表的就是精度为10个m_unit
    int             m_nAccuracy;

    // 1像素与物理长度的转换关系：如1000像素需要表示的长度为10000微米，则m_fConvert=10000微米/1000像素=10微米/像素
    float           m_fConvert;

    // 刻度尺的缩放系数
    //float           m_fZoom;    // 不能用浮点数计算，会出现精度问题
    int             m_nZoomFactor;

    // 刻度尺表示的物理单位，默认是毫米
    RulerUnit       m_unit;
    // 刻度尺单位（ nm/um/mm/cm/m/km ）
    QString         m_strRulerUnit;

    // 刻度的类型：水平刻度尺和垂直刻度尺，默认是水平刻度尺
    Qt::Orientation m_orientation;

    // 刻度尺0点的像素坐标
    QPointF         m_pointZero;
};
