#include "stdafx.h"
#include "ServerSocket.h"


ServerSocket::ServerSocket()
{
	WSADATA wsa = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsa);
}


ServerSocket::~ServerSocket()
{

}

void ServerSocket::createSocket()
{
	SOCKET server = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addr;
	int retVal;//调用Socket函数的返回值
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8977);
	addr.sin_addr.s_addr = htons(INADDR_ANY);

	::bind(server, (SOCKADDR*)&addr, sizeof(addr));
	listen(server, 20);
	//设置Socket为非阻塞模式
// 	int iMode = 1;
// 	retVal = ioctlsocket(server, FIONBIO, (u_long FAR*) &iMode);
// 	if (retVal == SOCKET_ERROR)
// 	{
// 		printf("ioctlsocket failed!\n");
// // 		WSACleanup();
// // 		return -1;
// 	}
	while (true)
	{

		SOCKADDR_IN client_addr;
		int len = sizeof(client_addr);
		SOCKET client = accept(server, (SOCKADDR*)&client_addr, &len);//与客户端通讯建立
		char host[32] = { 0 };
		inet_ntop(AF_INET, &client_addr.sin_addr, host, sizeof client_addr);
		cout << "clientIP:" << host << "linksuccess" << "套接字为:" << client << "\n";
		//发送信息线程
		std::thread t1(&ServerSocket::sendThread, this, client);
		t1.detach();
		//接收信息线程
		std::thread t2(&ServerSocket::recvThread, this, client);
		t2.detach();  //不能全部使用detach(),
					  //closesocket(client);
	}

	closesocket(server);

}

void ServerSocket::recvThread(SOCKET client)
{
	UserData user;
	char buffer[4108] = { 0 };
	string savePath("C:\\Users\\machao\\Desktop\\receive.txt");
	ofstream of(savePath, ios::binary | ios::out|ios::app);
	if (!of)
	{
		cout << "file fail to open" << endl;
	}
	else
	{
		cout << "yes" << endl;
	}
	while (true)
	{
		ZeroMemory(buffer, sizeof buffer);
		int res = recv(client, buffer, sizeof(buffer), 0);
		int a = 0;
		int b = 0;
		int data_length = 0;
		memcpy(&a, buffer, 4);
		char temp[4] = { 0 };
		memcpy(&b, buffer+4, 4);
		memcpy(&data_length, buffer + 8, 4);
		cout << "a的值为:" << a << "b的值为:" << b << "c的值为:" << data_length << endl;
		char d[4200] = { 0 };
	//	cout << "牛皮1" << endl;
		strncpy(d, buffer + 12, data_length);
		//cout << "牛皮2" << endl;
		if (res <= 0) 
		{
			break;
		}
		
		if (res > 0)
		{
			//cout << "牛皮3" << endl;
			cout << "收到的字节数:" << res << endl;
			of.write(d, data_length);
		}
	}
}

void ServerSocket::sendThread(SOCKET client)
{
	// 	while (true){
	// 		UserData send_data(25, "v", "11111", "zhangsaobao", "1900-02-31");
	// 		sendMSG(send_data, client);
	// 		Sleep(3000);
	// 	}	
}

bool ServerSocket::sendMSG(UserData & send_struct, SOCKET client)
{
	char send_buf[1024] = { 0 };
	send_struct.cmd = 1;
	send_struct.totalsize = sizeof(UserData);
	int sendres = send(client, (char*)&send_struct, sizeof(UserData), 0);//
	cout << "sendres->>" << sendres << endl;
	if (sendres > 0) {
		cout << "success to send!";
		return true;
	}
	else if (sendres <= 0) {
		cout << "fail to send!!!";
		return false;
	}
	send_buf[1024] = { 0 };
}
