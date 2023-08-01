#include "Draw.h"
#include "GraphicsItems.h"
#include "GraphicsView.h"
#include "GraphicsScene.h"

#include <QGraphicsRectItem>

CDraw::CDraw(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    InitWidget();
    ConnectSlot();

    this->showMaximized();
}

void CDraw::InitWidget()
{
    /************** View GroupBox *****************/
    m_pView = new CGraphicsView(this);
    m_pScene = new CGraphicsScene(this);
    m_pRectItem = new CRectItem(m_pScene);

    //m_pScene->setSceneRect(-INT_MAX/2,-INT_MAX/2,INT_MAX,INT_MAX);
    m_pScene->setSceneRect(-400 / 2, -400 / 2, 400, 400);

    QHBoxLayout *pViewLayout = new QHBoxLayout;
    pViewLayout->addWidget(m_pView);
    ui.ViewBox->setLayout(pViewLayout);

    m_pView->setScene(m_pScene);
    m_pView->centerOn(0, 0);

    m_pScene->addItem(m_pRectItem);
    m_pRectItem->setPos(-100, 0);


    /************** Control GroupBox *****************/
    ui.viewUpdateModeComBox->addItem("FullViewportUpdate");
    ui.viewUpdateModeComBox->addItem("MinimalViewportUpdate");
    ui.viewUpdateModeComBox->addItem("SmartViewportUpdate");
    ui.viewUpdateModeComBox->addItem("BoundingRectViewportUpdate");
    ui.viewUpdateModeComBox->addItem("NoViewportUpdate");

}

void CDraw::ConnectSlot()
{
}

void CDraw::resizeEvent(QResizeEvent * event)
{
    m_pView->centerOn(0, 0);
}

void CDraw::on_viewUpdateModeComBox_currentIndexChanged(int nIndex)
{
    m_pView->setViewportUpdateMode((QGraphicsView::ViewportUpdateMode)nIndex);
    m_pView->viewport()->update();
}

void CDraw::on_rectBtn_clicked()
{

}
