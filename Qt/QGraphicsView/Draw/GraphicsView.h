#pragma once

#include <QGraphicsView>

class CGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    CGraphicsView(QWidget *parent);
    ~CGraphicsView();

protected:
    virtual void paintEvent(QPaintEvent *event) override;
};
