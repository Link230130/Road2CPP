#pragma once

#include <QtWidgets/QWidget>
#include "ui_Draw.h"

class CGraphicsScene;
class CGraphicsView;
class CRectItem;

class QGraphicsRectItem;
class QGraphicsView;
class QGraphicsScene;

class CDraw : public QWidget
{
    Q_OBJECT

public:
    CDraw(QWidget *parent = Q_NULLPTR);
private:
    void InitWidget();
    void ConnectSlot();

public:

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_rectBtn_clicked();
    void on_viewUpdateModeComBox_currentIndexChanged(int nIndex);

private:
    CGraphicsScene*         m_pScene;
    CRectItem*              m_pRectItem;
    CGraphicsView*          m_pView;

private:
    Ui::CDrawClass ui;
};
