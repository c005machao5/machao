#include "videosurface.h"

VideoSurface::VideoSurface(QObject *parent)
    : QAbstractVideoSurface(parent)
{

}

bool VideoSurface::present(const QVideoFrame &frame)
{
    emit frameChanged(frame);
    return true;
}

QList<QVideoFrame::PixelFormat>
VideoSurface::supportedPixelFormats(
        QAbstractVideoBuffer::HandleType type) const
{
    return QList<QVideoFrame::PixelFormat>()
            << QVideoFrame::Format_RGB32;       //ARGB32
}
