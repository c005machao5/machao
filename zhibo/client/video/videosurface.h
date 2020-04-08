#ifndef VIDEOSURFACE_H
#define VIDEOSURFACE_H

#include <QObject>
#include <QAbstractVideoSurface>

//多媒体图片的处理
class VideoSurface:public QAbstractVideoSurface
{
    Q_OBJECT
public:
    explicit VideoSurface(QObject *parent = 0);

    //捕获处理的图片的  true 捕获成功 false 捕获失败
    virtual bool present(const QVideoFrame &frame);

    //设置图片处理的格式
    virtual QList<QVideoFrame::PixelFormat>
    supportedPixelFormats
    (QAbstractVideoBuffer::HandleType
     type = QAbstractVideoBuffer::NoHandle) const;
signals:
    void frameChanged(const QVideoFrame&);

public slots:
};

#endif // VIDEOSURFACE_H
