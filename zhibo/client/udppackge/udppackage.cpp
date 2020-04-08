#include "udppackage.h"

#include <Qdebug>

UdpPackage::UdpPackage()
{

}

QByteArray UdpPackage::pack_udp()
{
    //注意用指针赋值，将int转成四个字节的char存到QByteArray里
    QByteArray res;
    res.resize(this->info.size() + sizeof(int)*3);

    memcpy(res.data(), &(this->ID), sizeof(int));
    memcpy(res.data() + sizeof(int), &(this->curNum), sizeof(int));
    memcpy(res.data() + sizeof(int)*2, &(this->allNum), sizeof(int));
    memcpy(res.data() + sizeof(int)*3, this->info.data(), this->info.size());

    return res;
 }

int UdpPackage::unpack_udp(QByteArray& info)
{
    memcpy(&(this->ID),info.data(),sizeof(int));
    memcpy(&(this->curNum),info.data()+sizeof(int),sizeof(int));
    memcpy(&(this->allNum),info.data()+sizeof(int)*2,sizeof(int));
    this->info = info.right(info.size()-sizeof(int)*3);

    return this->info.size();
}
