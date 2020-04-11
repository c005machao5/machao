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
//MYSQL mysql, *sock;   //����MySQL�ľ��
//�����߳�
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
			cout << "������Ϣ������" << endl;
			break;
		}
		//cout << array << endl;
		cout << head_Packet.cmdType << endl;
		if (head_Packet.cmdType == 1)//�û�ע��
		{
			UserData user;
			memcpy(&user, array + sizeof(Head_Packet), sizeof(UserData));
			cout << "name =="<< user.name << endl;
			cout << "age  =="  <<user.age << endl;
			cout << user.passward << endl;
			cout << user.right << endl;
			cout << user.sex << endl;

			MysqlDB * db = MysqlDB::get_instance();//�����ݿ�
			Sqladd str;
			int n = str.inquire_name;
			if (n == 1)
			{
				return 1;//ע��ʧ�� �û����ظ�
			}
			else
			{
				bool res = db->exce(str.insert(user).c_str());
				cout << res << endl;
				return 0;//ע��ɹ�
			}
			
			MYSQL_RES * result = db->get_result("select * from user_surface");
			memset(array, 0, sizeof(array));
		}
		if (head_Packet.cmdType == 2)//��ʷ��ѯ
		{
			Data_Selection user;
			memcpy(&user, array + sizeof(Head_Packet), sizeof(Data_Selection));
			cout << "name ==" << user.data_time_type << endl;
			cout << "age  ==" << user.show_type<< endl;
			cout << "name ==" << user.time_select << endl;
			cout << "age  ==" << user.observe_well << endl;
			memset(array, 0, sizeof(array));

			MysqlDB * db = MysqlDB::get_instance();//�����ݿ�
			Sqladd str;
			
		}
		if (head_Packet.cmdType == 3)//����
		{
			Data_Analysis user;
			memcpy(&user, array + sizeof(Head_Packet), sizeof(Data_Analysis));
			cout << "name ==" << user.end_year << endl;
			cout << "age  ==" << user.observe_well << endl;
			cout << "name ==" << user.select_month << endl;
			cout << "age  ==" << user.start_year << endl;
			memset(array, 0, sizeof(array));
		}
		if (head_Packet.cmdType == 4)//���data
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
		if (head_Packet.cmdType == 5)//��¼
		{
			LoginInfo user;
			memcpy(&user, array + sizeof(Head_Packet), sizeof(LoginInfo));
			cout << "name ==" << user.name << endl;
			cout << "age  ==" << user.passward<< endl;
			cout << "age  ==" << user.userright<< endl;
			memset(array, 0, sizeof(array));

			MysqlDB * db = MysqlDB::get_instance();//�����ݿ�
			Sqladd str;//�����ݿ�
			int n = str.RegSql;
			if (n == 1)
			{
				return 1;//��¼�ɹ� �û����ظ�
			}
			else
			{
				return 0;//��¼ʧ��
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
	while ((row = mysql_fetch_row(result)) != NULL) //��ȡ������е����ݣ����ص�����һ�С���Ϊ��������ʱ����ǰ���α��ڵ�һ�С�֮ǰ��
	{
		cout << row[2] << endl;               //��ӡ��ǰ�еĵ�һ�е�����
											  //printf("age is %s\t\n", row[1]);              //��ӡ��ǰ�еĵڶ��е�����
	}*/

	WSAData wsd;
	WSAStartup(MAKEWORD(2, 2), &wsd);
	SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN ListenAddr;
	ListenAddr.sin_family = AF_INET;
	ListenAddr.sin_addr.S_un.S_addr = INADDR_ANY;//��ʾ���뱾��ip
	ListenAddr.sin_port = htons(PORT);
	int n;
	n = bind(ListenSocket, (LPSOCKADDR)&ListenAddr, sizeof(ListenAddr));
	if (n == SOCKET_ERROR) {
		cout << "�˿ڰ�ʧ�ܣ�" << endl;
		return -1;
	}
	else {
		cout << "�˿ڰ󶨳ɹ���" << PORT << endl;
	}
	int l = listen(ListenSocket, 20);
	cout << "�����׼���������ȴ���������" << endl;

	while (1) {
		//ѭ�����տͻ����������󲢴��������߳�
		SOCKET *ClientSocket = new SOCKET;
		ClientSocket = (SOCKET*)malloc(sizeof(SOCKET));
		//���տͻ�����������
		int SockAddrlen = sizeof(sockaddr);
		SOCKADDR_IN client_addr;
		int len = sizeof(SOCKADDR_IN);
		*ClientSocket = accept(ListenSocket, (sockaddr*)&client_addr, &len);
		sockerList.push_back(ClientSocket);
		cout << "һ���ͻ��������ӵ���������socket�ǣ�" << *ClientSocket << endl;
		CreateThread(NULL, 0, &ServerThread, sockerList.at(i), 0, NULL);
		++i;

	}//while
	closesocket(ListenSocket);
	WSACleanup();
	return(0);
}
