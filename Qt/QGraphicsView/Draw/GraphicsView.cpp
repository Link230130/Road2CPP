#include "GraphicsView.h"
#include <QPainter>

CGraphicsView::CGraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{
}

CGraphicsView::~CGraphicsView()
{
}

void CGraphicsView::paintEvent(QPaintEvent * event)
{
    QPainter painter(this->viewport());
    painter.setRenderHint(QPainter::Antialiasing,true);

#if 0
    // Draw Center Point
    painter.save();
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(5);
    painter.setPen(pen);
    painter.drawPoint(QPoint(this->width()/2,this->height()/2));
    painter.restore();
#endif

    QGraphicsView::paintEvent(event);
}
