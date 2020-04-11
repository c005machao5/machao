#pragma once

#include "stdafx.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <thread>
#include <iostream>
#include<fstream>
#include <string>
#include<mutex>
using namespace std;

//结构体声明
struct Head_Packet
{
	int cmd;
	int totalbytes;
};
//用户信息
struct UserData {
	int cmd;
	int totalsize;
	int  age;//判断标识
	char sex[4];    //性别
	char passward[24];  //密码
	char name[32];   //姓名
	char birthday[64];   //出生日期
	UserData()
	{
		age = 0;
		memset(sex, 0, sizeof(sex));
		memset(passward, 0, sizeof(passward));
		memset(name, 0, sizeof(name));
		memset(birthday, 0, sizeof(birthday));
	}
	UserData(int page, const char* psex, const char* ppass, const char* pname, const char* pbirthday)
	{
		age = page;
		strcpy(sex, psex);
		strcpy(passward, ppass);
		strcpy(name, pname);
		strcpy(birthday, pbirthday);
	}
};

class ServerSocket
{
public:
	ServerSocket();
	~ServerSocket();
	void createSocket();//创建socket
	void recvThread(SOCKET client);//接收线程
	void sendThread(SOCKET client);//发送线程
	bool sendMSG(UserData& send_struct, SOCKET client);//发送用户信息
	mutex g_mutex;
};

