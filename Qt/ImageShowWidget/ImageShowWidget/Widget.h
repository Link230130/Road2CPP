#pragma once

#include <QtWidgets/QWidget>
#include "ui_Widget.h"

#include "ImageDisplay.h"
#include <QTimer>

class CWidget : public QWidget
{
    Q_OBJECT

public:
    CWidget(QWidget *parent = Q_NULLPTR);


public slots:
    void on_btn_Update_clicked();
    void SlotTimeout();

private:
    CImageDisplay*  m_pImageDisplay;
    QTimer          m_timer;

private:
    Ui::CWidget ui;
};
