#include "ImageDisplay.h"

#include <QPainter>
#include <QDebug>
#include <QFile>


CImageDisplay::CImageDisplay(QWidget *parent)
    : QWidget(parent)
    , m_pBufer(nullptr)
    , m_nBufferSize(0)
    , m_nImageWidth(2448)
    , m_nImageHeight(2048)
    , m_nImageChannel(3)
{
    m_nBufferSize = m_nImageWidth * m_nImageHeight * m_nImageChannel;
    m_pBufer = new char[m_nBufferSize];
    memset(m_pBufer, 120, m_nBufferSize);

    m_image = QImage(m_nImageWidth, m_nImageHeight, QImage::Format_RGB888);
    const uchar* pBits = m_image.constBits();
    m_pRandom = new QRandomGenerator();
}

CImageDisplay::~CImageDisplay()
{
}

bool CImageDisplay::UpdateImage(uchar * pData, int nWidth, int nHeight, int nChannel)
{
    if (pData == nullptr || nWidth * nHeight * nChannel > m_nBufferSize)
    {
        return false;
    }
    if (m_image.loadFromData(pData, nWidth * nHeight * nChannel))
    {
        update();
        return true;
    }
    return false;
}

bool CImageDisplay::UpdateImage()
{
    int nValue = m_pRandom->bounded(0, 255);
    memset(m_pBufer, nValue, m_nBufferSize);

#if 0
    const uchar* pBits = m_image.constBits();
    memcpy((void*)pBits, m_pBufer, m_nBufferSize);
    update();

#else
    //m_image = QImage((uchar*)m_pBufer, m_nImageWidth, m_nImageHeight, QImage::Format_RGB888);;
    update();
#endif
    return true;
}

void CImageDisplay::paintEvent(QPaintEvent * event)
{
    QPainter p(this);

    p.save();
    double dWithScale = this->rect().width() * 1.0 / m_image.width();
    double dHeightScale = this->rect().height() * 1.0 / m_image.height();
    double dScale = dWithScale <= dHeightScale ? dWithScale : dHeightScale;
    p.scale(dScale, dScale);
    p.drawImage(QPoint(0, 0), QImage((uchar*)m_pBufer,m_nImageWidth,m_nImageHeight,QImage::Format_RGB888));
    p.restore();

    //qDebug() << "CImageDisplay paintEvent --> nWith = "
    //    << this->rect().width()
    //    << ",nHeight =" << this->rect().height()
    //    << "dScale=" << dScale;
}
