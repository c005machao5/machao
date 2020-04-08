#ifndef XINCAMERA_H
#define XINCAMERA_H

#include <QObject>

#include <QTimer>
#include <QLabel>
#include <QCamera>
#include <QUdpSocket>
#include "VideoSurface.h"
#include "udppackge/udppackage.h"

class XinCamera : public QObject
{
    Q_OBJECT

private:
    QLabel *lb;//用于显示的label

    QCamera* cam;
    VideoSurface* vs;

    QUdpSocket* readSocket;
    QUdpSocket* writeSocket;
    uint32_t port;

    int IDPk;
    int curPk;
    int allPk;
    QByteArray buffPk[4];

    QTimer *timer;
    int flag;//搭配定时器，每隔一段时间检测是否置1（有数据接收），否则label清屏

    void myWrite(QByteArray& info,int gate);

public:
    explicit XinCamera(QObject *parent = nullptr);
    //初始化时传入需要显示的label，和端口号
    XinCamera(QLabel *lb,uint32_t port,QObject *parent = nullptr);

    //外部接口,开启功能
    void cameraStart();
    void cameraStop();

signals:

public slots:
    void frameChangedSlot(QVideoFrame frame);
    void readyreadSlot();

    void onTimeoutSLot();
};

#endif // XINCAMERA_H
