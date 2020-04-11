#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <QByteArray>
#include <QDebug>
#include "signal_s.h"


class ClientSocket
{
    //Q_OBJECT
public:
    ClientSocket();
    ~ClientSocket();
    bool m_connect_socket(char* ip, int port);
    void sendMSG(UserData& send_struct);
    void sendMSG(Data_Selection& send_struct);
    void sendMSG(Data_Analysis& send_struct);
    void sendMSG(Data& send_struct);
    void sendMSG(LoginInfo& send_struct);
    void recvThread(SOCKET m_client_socket);
private:
    void reveMSG();
private:
    SOCKET m_client_socket;
    SOCKADDR_IN addr;
    WSADATA ws_data;
    QByteArray recv_data_array;
    Head_Packet head;
    UserData    userdata;
    Data_Selection data_select;
    Data_Analysis  data_analysis;
    Data data;
    LoginInfo logininfo;
public:
    signal_s sig;
//signals:
    //void recvData(Data);

};

#endif // CLIENTSOCKET_H
