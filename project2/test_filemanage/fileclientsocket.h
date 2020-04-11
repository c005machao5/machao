#ifndef FILECLIENTSOCKET_H
#define FILECLIENTSOCKET_H
#include <winsock2.h>
#include <ws2tcpip.h>
#include <QByteArray>
#include <thread>
#include <QDebug>
#include "structural.h"
//
class FileclientSocket
{
public:
    FileclientSocket();
    ~FileclientSocket();
    bool socketConnect(char* ip,int port);
    int socketRecv(char* buffer,int len);//返回值表示长度，入参buf缓冲区，用来保存数据,len表示缓冲区长度
    void sendMsg(UserData& send_msg);
    void sendMsg(char* buffer,int pnum);
private:
    SOCKET m_client_socket;
    int i=0;
};

#endif // FILECLIENTSOCKET_H
