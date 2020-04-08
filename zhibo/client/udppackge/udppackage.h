#ifndef UDPPACKAGE_H
#define UDPPACKAGE_H

#include <QByteArray>
class UdpPackage
{
private:
    int ID;
    int curNum;
    int allNum;
    QByteArray info;
public:
    UdpPackage();

    void setID(int id){ this->ID = id; }
    void setCurNum(int curNum){ this->curNum = curNum; }
    void setAllNum(int allNum){ this->allNum = allNum; }
    void setInfo(const QByteArray& info){ this->info = info; }

    int getID(void){ return this->ID; }
    int getCurNum(void){ return this->curNum; }
    int getAllNum(void){ return this->allNum; }
    QByteArray& getInfo(void){ return this->info; }

    QByteArray pack_udp();//当前结构体转换成QByteArray
    int unpack_udp(QByteArray& info);
};

#endif // UDPPACKAGE_H
