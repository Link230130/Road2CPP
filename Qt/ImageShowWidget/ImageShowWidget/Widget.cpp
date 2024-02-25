#include "Widget.h"
#include <QDebug>

CWidget::CWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    m_pImageDisplay = new CImageDisplay();

    QLayout* pLayout = ui.widget->layout();
    pLayout->addWidget(m_pImageDisplay);

    connect(&m_timer, &QTimer::timeout, this, &CWidget::SlotTimeout);
}

void CWidget::on_btn_Update_clicked()
{
    if (m_timer.isActive())
    {
        m_timer.stop();
    }
    else
    {
        m_timer.start(1000 / 90);
    }

}

void CWidget::SlotTimeout()
{
    if (m_pImageDisplay)
    {
        if (!m_pImageDisplay->UpdateImage())
        {
            qDebug() << "Update image failed!";
        }
    }
}
