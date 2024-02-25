#pragma once

#include <QWidget>
#include <QImage>
#include <QRandomGenerator>

class CImageDisplay : public QWidget
{
    Q_OBJECT

public:
    CImageDisplay(QWidget *parent = nullptr);
    ~CImageDisplay();

    bool UpdateImage(uchar* pData, int nWidth, int nHeight, int nChannel);

    bool UpdateImage();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QImage              m_image;
    int                 m_nImageWidth;
    int                 m_nImageHeight;
    int                 m_nImageChannel;


    char*               m_pBufer;
    int                 m_nBufferSize;

    QRandomGenerator*   m_pRandom;
};
