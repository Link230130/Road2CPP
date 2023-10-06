#include "RulerWidget.h"

#include <QPainter>
#include <QWheelEvent>
#include <QDebug>

RulerWidget::RulerWidget(QWidget *parent)
    : QWidget(parent)
    , m_fConvert(10.0f)
    , m_nIntervalPixel(10)
    , m_nAccuracy(1)
    , m_nZoomFactor(100)
    , m_unit(RulerUnit::MM)
    , m_strRulerUnit("mm")
    , m_orientation(Qt::Horizontal)
{

}

RulerWidget::~RulerWidget()
{
}

void RulerWidget::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 设置字体
    // painter.setFont();

    QPen pen(Qt::black, 1);
    pen.setWidth(1);

    painter.setPen(pen);
    painter.translate(0, 0);

    painter.fillRect(this->rect(), QColor(239, 239, 239));

    if (m_orientation == Qt::Horizontal)
    {
        DrawHorizontalRuler(&painter, &pen);
    }
    else
    {
        DrawVerticalRuler(&painter, &pen);
    }
}

void RulerWidget::wheelEvent(QWheelEvent *event)
{
    if (event->delta() < 0)
    {
        // 最多缩小到原图
        if (m_nZoomFactor <= 100)
        {
            return;
        }
        // 缩小百分之10
        m_nZoomFactor -= 10;
    }
    else
    {
        // 放大百分之10
        m_nZoomFactor += 10;
    }
    qDebug() << "m_nZoomFactor=" << m_nZoomFactor;
    update();
    QWidget::wheelEvent(event);
}

void RulerWidget::DrawHorizontalRuler(QPainter * painter, QPen * pen)
{
    // 1.确定0点位置
    m_pointZero.setX(45);
    m_pointZero.setY(this->height() - 45.0);

    // 2.绘制直线
    QPointF startPointF(0, m_pointZero.y());
    QPointF endPointF(this->width(), m_pointZero.y());
    painter->drawLine(startPointF, endPointF);

    // 判断当前的放大倍数
    int nScaleFactor = 1;
    if (m_nZoomFactor % 100 == 0)
    {
        nScaleFactor = m_nZoomFactor / 100;
    }

    // 3.绘制刻度
    float fScaleLeft = m_pointZero.x();
    // 刻度序号
    int nIndex = 0;
    // 刻度高度
    int nScaleHeight = 20;
    QString strScaleText;
    while (fScaleLeft < this->width())
    {
        strScaleText.clear();
        if (nIndex % 10 == 0)
        {
            // 刻度高度调整
            nScaleHeight = 15;
            strScaleText = QString::number(nIndex*nScaleFactor / 10) + m_strRulerUnit;
            // 绘制刻度文本
            if (1)
            {
                // todo 可设置文本在刻度上面或是下面
                painter->drawText(QPoint(fScaleLeft, m_pointZero.y() + nScaleHeight + 15), strScaleText);
            }
        }
        else
        {
            // 中间刻度的高度比普通刻度要长
            nScaleHeight = (nIndex % 5 == 0) ? 10 : 6;
        }
        // todo 可设置刻度是在横线上面或是下面
        if (1)
        {
            painter->drawRect(QRectF(fScaleLeft, m_pointZero.y() - nScaleHeight, 0.1, nScaleHeight));
        }

        fScaleLeft += m_nIntervalPixel * (m_nZoomFactor / 100.0);
        nIndex++;
    }

}

void RulerWidget::SetUnit(RulerUnit unit)
{
    m_unit = unit;
    switch (m_unit)
    {
    case RulerUnit::NM:
        m_strRulerUnit = "nm";
        break;
    case RulerUnit::UM:
        m_strRulerUnit = "um";
        break;
    case RulerUnit::MM:
        m_strRulerUnit = "mm";
        break;
    case RulerUnit::CM:
        m_strRulerUnit = "cm";
        break;
    case RulerUnit::M:
        m_strRulerUnit = "m";
        break;
    case RulerUnit::KM:
        m_strRulerUnit = "km";
        break;
    default:
        break;
    }

    this->update();
}

void RulerWidget::DrawVerticalRuler(QPainter * painter, QPen * pen)
{
}
