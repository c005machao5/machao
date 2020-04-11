#pragma once

#include "stdafx.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <thread>
#include <iostream>
#include <string>
#include <mutex>
#include <list>
using namespace std;

typedef list<pair<SOCKET, DWORD>> ClientList;

//�ṹ������
struct Head_Packet
{
	int cmd;
	int totalbytes;
};
//�û���Ϣ
struct UserData {
	int cmd;
	int totalsize;
	int  age;//�жϱ�ʶ
	char sex[4];    //�Ա�
	char passward[24];  //����
	char name[32];   //����
	char birthday[64];   //��������
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

class FileserverSocket
{
public:
	FileserverSocket();
	~FileserverSocket();
	void createSocket();//����socket
	void recvThread(SOCKET client);//�����߳�
	void sendThread(SOCKET client);//�����߳�
	bool sendMSG(UserData& send_struct, SOCKET client);//�����û���Ϣ
	ClientList& GetClientList();
private:
	mutex qmutex;
	DWORD dwstart;
	ClientList clientlist;
};
