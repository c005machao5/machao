#include "fileclientsocket.h"

//构造函数进行初始化
FileclientSocket::FileclientSocket()
{
    WSADATA wsa={0};
    WSAStartup(MAKEWORD(2,2),&wsa);
}
//关闭socket()
FileclientSocket::~FileclientSocket()
{
    //close();
    closesocket(m_client_socket);
    WSACleanup();
}
//socket()创建和connect()
bool FileclientSocket::socketConnect(char *ip, int port)
{
    //创建socket
    m_client_socket=socket(AF_INET,SOCK_STREAM,0);
    SOCKADDR_IN addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port);
    //inet_pton(AF_INET,"127.0.0.1",&addr.sin_addr);//不识别
    addr.sin_addr.S_un.S_addr=inet_addr(ip);
    //请求连接
    //::connect(client_socket,(SOCKADDR*)&addr,sizeof(addr));
    int ret=::connect(m_client_socket,(SOCKADDR*)&addr,sizeof(addr));
    if(ret==0){
        qDebug()<<"success to connect!";
        return true;
    }
    else if(ret<0){
        qDebug()<<"fail to connect!!!";
        return false;
    }
    return 0;
}
//接收收据，主窗口另起线程
// 返回值表示长度，入参buf缓冲区，用来保存数据,len表示缓冲区长度
int FileclientSocket::socketRecv(char *buffer, int len)
{
    int recvres=recv(m_client_socket,buffer,len,0);
    return recvres;
}
//发送信息
void FileclientSocket::sendMsg(UserData& send_msg)
{
    QByteArray send_buf={0};
    send_msg.cmd=1;
    int len=send_msg.totalsize=sizeof(UserData);
    send_buf.resize(len);
    memcpy(send_buf.data(),&send_msg,sizeof(UserData));
    int sendres=send(m_client_socket,send_buf.toStdString().c_str(),send_buf.size(),0);
    if(sendres>0){
        qDebug()<<"success to send!";
    }
    else if(sendres<=0){
        qDebug()<<"fail to send!!!";
    }
    send_buf.resize(0);//每发送一次将缓冲区置为0
}

void FileclientSocket::sendMsg(char* buffer,int pnum)
{
    qDebug()<<"buffer"<<buffer<<endl;
    FileMsg send_msg;
    QByteArray send_buf;
    send_msg.cmd=2;//结构体编号
    send_msg.num=pnum;//当前块
    int length=10;
    send_buf.resize(length);
    memcpy(send_buf.data(),buffer,length);
    qDebug()<<"send_buf"<<send_buf.data()<<endl;
    int sendres=send(m_client_socket,send_buf.toStdString().c_str(),send_buf.size(),0);
    if(sendres>0){
        qDebug()<<"success to send!"<<m_client_socket;
    }
    else if(sendres<=0){
        qDebug()<<"fail to send!!!";
    }
    send_buf.resize(0);//每发送一次将缓冲区置为0
}
