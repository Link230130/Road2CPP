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

    // ��������
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
        // �����С��ԭͼ
        if (m_nZoomFactor <= 100)
        {
            return;
        }
        // ��С�ٷ�֮10
        m_nZoomFactor -= 10;
    }
    else
    {
        // �Ŵ�ٷ�֮10
        m_nZoomFactor += 10;
    }
    qDebug() << "m_nZoomFactor=" << m_nZoomFactor;
    update();
    QWidget::wheelEvent(event);
}

void RulerWidget::DrawHorizontalRuler(QPainter * painter, QPen * pen)
{
    // 1.ȷ��0��λ��
    m_pointZero.setX(45);
    m_pointZero.setY(this->height() - 45.0);

    // 2.����ֱ��
    QPointF startPointF(0, m_pointZero.y());
    QPointF endPointF(this->width(), m_pointZero.y());
    painter->drawLine(startPointF, endPointF);

    // �жϵ�ǰ�ķŴ���
    int nScaleFactor = 1;
    if (m_nZoomFactor % 100 == 0)
    {
        nScaleFactor = m_nZoomFactor / 100;
    }

    // 3.���ƿ̶�
    float fScaleLeft = m_pointZero.x();
    // �̶����
    int nIndex = 0;
    // �̶ȸ߶�
    int nScaleHeight = 20;
    QString strScaleText;
    while (fScaleLeft < this->width())
    {
        strScaleText.clear();
        if (nIndex % 10 == 0)
        {
            // �̶ȸ߶ȵ���
            nScaleHeight = 15;
            strScaleText = QString::number(nIndex*nScaleFactor / 10) + m_strRulerUnit;
            // ���ƿ̶��ı�
            if (1)
            {
                // todo �������ı��ڿ̶������������
                painter->drawText(QPoint(fScaleLeft, m_pointZero.y() + nScaleHeight + 15), strScaleText);
            }
        }
        else
        {
            // �м�̶ȵĸ߶ȱ���ͨ�̶�Ҫ��
            nScaleHeight = (nIndex % 5 == 0) ? 10 : 6;
        }
        // todo �����ÿ̶����ں��������������
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
