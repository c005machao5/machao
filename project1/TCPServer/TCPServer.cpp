#include"stdafx.h"
#include <cstdio>
#include<iostream>
#include<string>
#include<WinSock2.h>
#include<Windows.h>
#include <vector>
#include "StructData.h"
#include "MysqlDB.h"
#include <mysql.h>
#include "Sqladd.h"

#pragma comment(lib,"ws2_32.lib")
//using namespace std;
const int PORT = 8000;
#define MaxClient 10
#define MaxBufSize 1024*4
#define _CRT_SECURE_NO_WARINGS
static int i = 0;
//MYSQL mysql, *sock;   //声明MySQL的句柄
//服务线程
DWORD WINAPI ServerThread(LPVOID lpParameter) {
	SOCKET *ClientSocket = (SOCKET*)lpParameter;
	cout << "i===" << i << endl;
	int receByt = 0;
	char array[MaxBufSize] = {0};
	char SendBuf[MaxBufSize] = {0};
	while (1) {
		receByt = recv(*ClientSocket, array, sizeof(array), 0);
		Head_Packet head_Packet;
		memcpy(&head_Packet, array, sizeof(Head_Packet));
		//buf[receByt]='\0';
		//cout << head_Packet.cmdType << head_Packet.totalbytes << endl;
		if(head_Packet.cmdType ==0 || receByt == -1)
		{
			cout << "接收消息结束！" << endl;
			break;
		}
		//cout << array << endl;
		cout << head_Packet.cmdType << endl;
		if (head_Packet.cmdType == 1)//用户注册
		{
			UserData user;
			memcpy(&user, array + sizeof(Head_Packet), sizeof(UserData));
			cout << "name =="<< user.name << endl;
			cout << "age  =="  <<user.age << endl;
			cout << user.passward << endl;
			cout << user.right << endl;
			cout << user.sex << endl;

			MysqlDB * db = MysqlDB::get_instance();//存数据库
			Sqladd str;
			int n = str.inquire_name;
			if (n == 1)
			{
				return 1;//注册失败 用户名重复
			}
			else
			{
				bool res = db->exce(str.insert(user).c_str());
				cout << res << endl;
				return 0;//注册成功
			}
			
			MYSQL_RES * result = db->get_result("select * from user_surface");
			memset(array, 0, sizeof(array));
		}
		if (head_Packet.cmdType == 2)//历史查询
		{
			Data_Selection user;
			memcpy(&user, array + sizeof(Head_Packet), sizeof(Data_Selection));
			cout << "name ==" << user.data_time_type << endl;
			cout << "age  ==" << user.show_type<< endl;
			cout << "name ==" << user.time_select << endl;
			cout << "age  ==" << user.observe_well << endl;
			memset(array, 0, sizeof(array));

			MysqlDB * db = MysqlDB::get_instance();//存数据库
			Sqladd str;
			
		}
		if (head_Packet.cmdType == 3)//分析
		{
			Data_Analysis user;
			memcpy(&user, array + sizeof(Head_Packet), sizeof(Data_Analysis));
			cout << "name ==" << user.end_year << endl;
			cout << "age  ==" << user.observe_well << endl;
			cout << "name ==" << user.select_month << endl;
			cout << "age  ==" << user.start_year << endl;
			memset(array, 0, sizeof(array));
		}
		if (head_Packet.cmdType == 4)//李迪data
		{
			Data user;
			memcpy(&user, array + sizeof(Head_Packet), sizeof(Data));
			cout << "name ==" << user.longitude << endl;
			cout << "age  ==" << user.level << endl;
			cout << "name ==" << user.latitude << endl;
			cout << "age  ==" << user.GPRS << endl;
			cout << "name ==" << user.FLUG << endl;
			cout << "age  ==" << user.depth << endl;
			cout << "name ==" << user.name << endl;
			cout << "age  ==" << user.corp << endl;
			cout << "age  ==" << user.AD<< endl;
			memset(array, 0, sizeof(array));
		}
		if (head_Packet.cmdType == 5)//登录
		{
			LoginInfo user;
			memcpy(&user, array + sizeof(Head_Packet), sizeof(LoginInfo));
			cout << "name ==" << user.name << endl;
			cout << "age  ==" << user.passward<< endl;
			cout << "age  ==" << user.userright<< endl;
			memset(array, 0, sizeof(array));

			MysqlDB * db = MysqlDB::get_instance();//存数据库
			Sqladd str;//存数据库
			int n = str.RegSql;
			if (n == 1)
			{
				return 1;//登录成功 用户名重复
			}
			else
			{
				return 0;//登录失败
			}
		}
		
		memset(array, 0, sizeof(array));
	}
	closesocket(*ClientSocket);
	free(ClientSocket);
	return 0;
}
vector<SOCKET *> sockerList;


int main() {

	/*MysqlDB * db = MysqlDB::get_instance();
	bool res = db->change_table("delete from user_surface where user_surface_id = 1");
	cout << res << endl;
	MYSQL_RES * result = db->get_result("select * from user_surface");
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(result)) != NULL) //读取结果集中的数据，返回的是下一行。因为保存结果集时，当前的游标在第一行【之前】
	{
		cout << row[2] << endl;               //打印当前行的第一列的数据
											  //printf("age is %s\t\n", row[1]);              //打印当前行的第二列的数据
	}*/

	WSAData wsd;
	WSAStartup(MAKEWORD(2, 2), &wsd);
	SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN ListenAddr;
	ListenAddr.sin_family = AF_INET;
	ListenAddr.sin_addr.S_un.S_addr = INADDR_ANY;//表示填入本机ip
	ListenAddr.sin_port = htons(PORT);
	int n;
	n = bind(ListenSocket, (LPSOCKADDR)&ListenAddr, sizeof(ListenAddr));
	if (n == SOCKET_ERROR) {
		cout << "端口绑定失败！" << endl;
		return -1;
	}
	else {
		cout << "端口绑定成功：" << PORT << endl;
	}
	int l = listen(ListenSocket, 20);
	cout << "服务端准备就绪，等待连接请求" << endl;

	while (1) {
		//循环接收客户端连接请求并创建服务线程
		SOCKET *ClientSocket = new SOCKET;
		ClientSocket = (SOCKET*)malloc(sizeof(SOCKET));
		//接收客户端连接请求
		int SockAddrlen = sizeof(sockaddr);
		SOCKADDR_IN client_addr;
		int len = sizeof(SOCKADDR_IN);
		*ClientSocket = accept(ListenSocket, (sockaddr*)&client_addr, &len);
		sockerList.push_back(ClientSocket);
		cout << "一个客户端已连接到服务器，socket是：" << *ClientSocket << endl;
		CreateThread(NULL, 0, &ServerThread, sockerList.at(i), 0, NULL);
		++i;

	}//while
	closesocket(ListenSocket);
	WSACleanup();
	return(0);
}
