#include "clientsocket.h"

ClientSocket::ClientSocket()
{

    WSAStartup(MAKEWORD(2, 2), &ws_data);

}


ClientSocket::~ClientSocket()
{
    closesocket(m_client_socket);
    WSACleanup();
}
bool ClientSocket::m_connect_socket(char* ip, int port)
{
    m_client_socket = socket(AF_INET, SOCK_STREAM, 0);


    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.S_un.S_addr = inet_addr(ip);
    //inet_pton(AF_INET, ip, &addr.sin_addr);
    //::connect(m_client_socket,(SOCKADDR*)&addr,sizeof(addr));
    int connect_res=::connect(m_client_socket,(SOCKADDR*)&addr,sizeof(addr));
    if (connect_res == 0)
    {
        reveMSG();
        qDebug() << "客户端连接成功";
        return true;
    }
    else if (connect_res < 0)
    {
        qDebug() << "客户端连接失败";
        return false;
    }
}
void ClientSocket::sendMSG(UserData& send_struct)
{
    QByteArray send_array = { 0 };
    send_struct.cmdnum = 1;
    send_struct.totalsize = sizeof(UserData);
    send_array.resize(send_struct.totalsize);
    memcpy(send_array.data(), &send_struct, sizeof(UserData));
    int sendres=send(m_client_socket,send_array.toStdString().c_str(),send_array.size(),0);
    if(sendres==-1)
    {
        qDebug()<<"发送失败";
    }
    else if(sendres==0)
    {
        qDebug()<<"发送端口正常";
    }
    else if(sendres>0)
    {
        qDebug()<<"发送成功";
    }
    send_array.resize(0);
}
void ClientSocket::sendMSG(Data_Selection& send_struct)
{
    QByteArray send_array = { 0 };
    send_struct.cmdnum = 2;
    send_struct.totalsize = sizeof(Data_Selection);
    send_array.resize(send_struct.totalsize);
    memcpy(send_array.data(), &send_struct, sizeof(Data_Selection));
    int sendres=send(m_client_socket,send_array.toStdString().c_str(),send_array.size(),0);
    if(sendres==-1)
    {
        qDebug()<<"发送失败";
    }
    else if(sendres==0)
    {
        qDebug()<<"发送端口正常";
    }
    else if(sendres>0)
    {
        qDebug()<<"发送成功";
    }
    send_array.resize(0);
}

void ClientSocket::sendMSG(Data_Analysis& send_struct)
{
    QByteArray send_array = { 0 };
    send_struct.cmdnum = 3;
    send_struct.totalsize = sizeof(Data_Analysis);
    send_array.resize(send_struct.totalsize);
    memcpy(send_array.data(), &send_struct, sizeof(Data_Analysis));
    int sendres=send(m_client_socket,send_array.toStdString().c_str(),send_array.size(),0);
    if(sendres==-1)
    {
        qDebug()<<"发送失败";
    }
    else if(sendres==0)
    {
        qDebug()<<"发送端口正常";
    }
    else if(sendres>0)
    {
        qDebug()<<"发送成功";
    }
    send_array.resize(0);
}
void ClientSocket::sendMSG(Data& send_struct)
{
    QByteArray send_array = { 0 };
    send_struct.cmdnum = 4;
    send_struct.totalsize = sizeof(Data);
    send_array.resize(send_struct.totalsize);
    memcpy(send_array.data(), &send_struct, sizeof(Data));
    int sendres=send(m_client_socket,send_array.toStdString().c_str(),send_array.size(),0);
    if(sendres==-1)
    {
        qDebug()<<"发送失败";
    }
    else if(sendres==0)
    {
        qDebug()<<"发送端口正常";
    }
    else if(sendres>0)
    {
        qDebug()<<"发送成功";
    }
    send_array.resize(0);
}
void ClientSocket::sendMSG(LoginInfo& send_struct)
{
    QByteArray send_array = { 0 };
    send_struct.cmdnum = 5;
    send_struct.totalsize = sizeof(LoginInfo);
    send_array.resize(send_struct.totalsize);
    memcpy(send_array.data(), &send_struct, sizeof(LoginInfo));
    int sendres=send(m_client_socket,send_array.toStdString().c_str(),send_array.size(),0);
    if(sendres==-1)
    {
        qDebug()<<"发送失败";
    }
    else if(sendres==0)
    {
        qDebug()<<"发送端口正常";
    }
    else if(sendres>0)
    {
        qDebug()<<"发送成功";
    }
    send_array.resize(0);
}

void ClientSocket::recvThread(SOCKET m_client_socket)
{
    while(true)
    {
        //qDebug()<<"recv come in...";
        //包头解析
        char recv_buffer[320]={0};
        recv_data_array.resize(320);
        int recvres=recv(m_client_socket,recv_buffer,sizeof(recv_buffer),0);
        memcpy(recv_data_array.data(),recv_buffer,sizeof(recv_buffer));
        memcpy(&head,recv_data_array.data(),sizeof(Head_Packet));
        if(recvres>0)
        {
            qDebug()<<"数据接收成功";
        }
        else if(recvres==0)
        {
            qDebug()<<"数据接收端正常";
        }
        else if(recvres<0)
        {
           qDebug()<<"数据接收失败,断开连接";
           break;
        }
        //数据解析
        if(head.cmdType==1)
        {
            memcpy(&userdata,recv_data_array.data(),sizeof(UserData));
            emit sig.client_socket_signal(userdata);
            qDebug()<<"name:"<<userdata.name<<"\n"\
                     <<"age:"<<userdata.age<<"\n"\
                     <<"sex:"<<userdata.sex<<"\n"\
                     <<"birthday:"<<userdata.birthday<<"\n"\
                     <<"tel:"<<userdata.tel<<"\n"\
                     <<"right:"<<userdata.right<<"\n"\
                     <<"passward:"<<userdata.passward;

        }

        else if(head.cmdType==2)
        {
            //QThread::sleep(1);
            memcpy(&data_select,recv_data_array.data(),sizeof(Data_Selection));
            emit sig.client_socket_signal(data_select);
           qDebug()<<"data_time_type:"<<data_select.data_time_type<<"\n"\
                    <<"observe_well:"<<data_select.observe_well<<"\n"\
                    <<"time_select:"<<data_select.time_select<<"\n"\
                    <<"show_type:"<<data_select.show_type;
        }

        else if(head.cmdType==3)
        {
            //QThread::sleep(1);
            memcpy(&data_analysis,recv_data_array.data(),sizeof(Data_Analysis));
            emit sig.client_socket_signal(data_analysis);
          qDebug()<<"start_year:"<<data_analysis.start_year<<"\n"\
                   <<"end_year:"<<data_analysis.end_year<<"\n"\
                   <<"observe_well:"<<data_analysis.observe_well<<"\n"\
                   <<"select_month:"<<data_analysis.select_month;
        }

        else if(head.cmdType==4)
        {
            //QThread::sleep(1);
            memcpy(&data,recv_data_array.data(),sizeof(Data));
            sig.recvData(data);
//         qDebug()<<"name:"<<data.name<<"\n"\
//                  <<"latitude:"<<data.latitude<<"\n"\
//                  <<"level:"<<data.level<<"\n"\
//                  <<"GPRS:"<<data.GPRS<<"\n"\
//                  <<"latitude:"<<data.latitude<<"\n"\
//                  <<"longitude:"<<data.longitude<<"\n"\
//                  <<"FLUG:"<<data.FLUG;
        }

        else if(head.cmdType==5)
        {
            //QThread::sleep(1);
            memcpy(&logininfo,recv_data_array.data(),sizeof(LoginInfo));
            emit sig.client_socket_signal(logininfo);
            qDebug()<<"name:"<<logininfo.name<<"\n"\
                     <<"passward:"<<logininfo.passward<<"\n"\
                     <<"userright:"<<logininfo.userright;
        }
        recv_data_array.resize(0);
    }
}

void ClientSocket::reveMSG()
{
    std::thread t1(&ClientSocket::recvThread,this,m_client_socket);
    //std::thread * th = new std::thread(&ClientSocket::recvThread,this,m_client_socket);
    t1.detach();
}
