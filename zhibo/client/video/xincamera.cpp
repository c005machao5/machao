#include "xincamera.h"

#include <QDebug>
#include <QCameraInfo>
#include <QAbstractVideoBuffer>
#include <QBuffer>
#include <QImageReader>

XinCamera::XinCamera(QObject *parent) : QObject(parent)
{

}

XinCamera::XinCamera(QLabel *lb,uint32_t port,QObject *parent)
    :QObject(parent)
{
    this->lb = lb;
    this->port = port;

    this->IDPk = 0;
    this->curPk = 0;
    this->allPk = 0;

    timer = new QTimer(this);
    flag = 0;
    connect(timer,SIGNAL(timeout()),
            this,SLOT(onTimeoutSLot()));
    timer->start(2500);

    //////////////////////////////////////////////////
    //获取计算机的默认摄像头
    QCameraInfo info = QCameraInfo::defaultCamera();
    cam = new QCamera(info, this);
    vs = new VideoSurface(this);

    //设置将多媒体文件显示到QVideoWidget窗口上
    cam->setViewfinder(vs);
    //对每一帧图片的处理
    connect(vs,SIGNAL(frameChanged(QVideoFrame)),
            this,SLOT(frameChangedSlot(QVideoFrame)));

    //////////////////////////////////////////////////
    writeSocket = new QUdpSocket(this);
    readSocket = new QUdpSocket(this);
    connect(this->readSocket, SIGNAL(readyRead()),
            this,SLOT(readyreadSlot()));
    readSocket->bind(QHostAddress::AnyIPv4,this->port,
                     QUdpSocket::ShareAddress
                     | QUdpSocket::ReuseAddressHint);

    readSocket->joinMulticastGroup(QHostAddress("224.0.0.220"));
}

void XinCamera::onTimeoutSLot()
{
    if(flag == 0){
        this->lb->clear();
    }
    else{
        flag = 0;
    }
}

//开启功能
void XinCamera::cameraStart()
{
    this->cam->start();
}
void XinCamera::cameraStop()
{
    this->cam->stop();
}

/****************************
**  摄像头采集到信号后触发的槽。
****************************/
void XinCamera::frameChangedSlot(QVideoFrame frame)
{
    frame.map(QAbstractVideoBuffer::ReadOnly);

    QImage img(
        frame.bits(),
        frame.width(),
        frame.height(),
        frame.bytesPerLine(),
        QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat())
        );

    img = img.scaled(500,309);//数据压缩

    /////////////////////////////////////////////////////////////////
    //将图片信息以广播组的形式发送出去
    QByteArray byte;
    QBuffer buffer(&byte);
    img.save(&buffer,"JPG");//这一句很耗时，会引起界面卡

    //将图片信息写入到制定端口
    //writeSocket->writeDatagram(byte,QHostAddress("224.0.0.220"), this->port);
    //writeSocket->writeDatagram(byte,QHostAddress::LocalHost, 8888);
    myWrite(byte,65000);
}

/**********************
**  摄像头信息UDP接收后
**********************/
void XinCamera::readyreadSlot()
{
    this->flag = 1;

    quint64 size = readSocket->pendingDatagramSize();
    QByteArray buff2;
    buff2.resize(size);
    readSocket->readDatagram(buff2.data(),buff2.size());//没这句，只触发一次信号

    //数据收齐了或者数据ID变了
    UdpPackage upack;
    upack.unpack_udp(buff2);
    this->curPk = upack.getCurNum();
    this->allPk = upack.getAllNum();

    if(this->curPk <= this->allPk){
        this->buffPk[0] += upack.getInfo();
    }
    //收齐数据
    if(this->curPk == this->allPk){

        QBuffer buffer(this->buffPk);
        QImageReader reader(&buffer,"JPEG");
        QImage img = reader.read();

        QMatrix matrix;
        matrix.rotate(180);//旋转图片180度
        img = img.transformed(matrix);

        QPixmap pix = QPixmap::fromImage(img);

        this->lb->setPixmap(pix.scaled(this->lb->size()));//读到数据应该显示在界面上，因此还是应该和界面紧密联系。

        for(int i=0;i<4;i++){
           this->buffPk[i].clear();
        }
    }
    qDebug()<<"收到...";
}

/********************
**  单包受限，分包发送
********************/
void XinCamera::myWrite(QByteArray& info,int gate)
{
    int len = info.size();

    int cur = 0;
    int all = len/gate+1;

    UdpPackage upack;
    upack.setID(1);
    upack.setAllNum(all);

    QByteArray send;
    while(len>0){
        cur++;
        upack.setCurNum(cur);

        if(len>gate){
            upack.setInfo(info.left(gate));

            send.resize(gate+sizeof(int)*3);
            send = upack.pack_udp();
            writeSocket->writeDatagram(send,QHostAddress("224.0.0.220"), this->port);

            info = info.right(len-gate);
            len -= gate;
        }
        else{
            upack.setInfo(info);

            send.resize(info.size()+sizeof(int)*3);
            send = upack.pack_udp();
            writeSocket->writeDatagram(send,QHostAddress("224.0.0.220"), this->port);

            len = 0;
        }
        send.clear();
        qDebug()<<"发送...";
    }
}
