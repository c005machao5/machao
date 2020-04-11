#include "stdafx.h"
#include "FileserverSocket.h"
#include<fstream>

FileserverSocket::FileserverSocket()
{
	WSADATA wsa = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsa);
}


FileserverSocket::~FileserverSocket()
{
	
}

void FileserverSocket::createSocket()
{
	SOCKET server = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8977);
	addr.sin_addr.s_addr = htons(INADDR_ANY);

	::bind(server, (SOCKADDR*)&addr, sizeof(addr));
	listen(server, 5);//循环监听时listen()需放在循环外边
	//接收信息线程
// 	std::thread t1(&FileserverSocket::recvThread, this, server);
// 	t1.join();
	
	while (true)
	{		
		SOCKADDR_IN client_addr;
		int len = sizeof(client_addr);
		SOCKET client = accept(server, (SOCKADDR*)&client_addr, &len);//与客户端通讯建立
	//	if (client ==SOCKET_ERROR) break;
		cout << "连接成功" << endl;
		clientlist.push_back(make_pair(client, GetTickCount()));//每有一个socket就存到容器中
		//发送信息线程
		cout << "牛皮" << endl;
		std::thread t2(&FileserverSocket::sendThread, this, client);
		t2.detach();
		std::thread t1(&FileserverSocket::recvThread, this, server);
		t1.detach();
		cout << "牛皮1" << endl;
		//closesocket(client);
	}	
	closesocket(server);	
}

void FileserverSocket::recvThread(SOCKET client)
{
	//UserData user;
	char buffer[10] = { 0 };
	//写入文件进行验证
	cout << "牛皮3" << endl;
	string savePath("C:\\Users\\4006006655\\Desktop\\b.txt");
	ofstream of(savePath, ios::binary | ios::out | ios::app);
	while (true) 
	{
		ZeroMemory(buffer, sizeof(buffer));
		//cout << "wait for ...recv" << endl;
		cout << "牛总好" << endl;
		cout << "验证套接字" << client << endl;
		int res = recv(client, buffer, sizeof(buffer), 0);
		cout << res << endl;
		ClientList& _list = GetClientList();//
// 		if (_list.size() == 0) {
// 			Sleep(10);
// 			continue;
// 		}
		//qmutex.lock();
	
		if (res>0)
		{
			qmutex.lock();
			cout << "接收正常" << endl;
			cout << "buffer:" << buffer << endl;
			qmutex.unlock();
		}
// 		for (ClientList::iterator iter = _list.begin(); iter != _list.end();)
// 		{
// 			Sleep(100);
// 			cout << clientlist.size() << endl;
// 			//int res = recv(client, buffer, sizeof(buffer), 0);
// 
// 			if (res ==0 )
// 			{
// 				
// 				cout << "客户端已断开连接" <<iter->first<< endl;
// 				//iter = _list.erase(iter);
// 			}
// 			else if (res == SOCKET_ERROR)
// 			{
// 				//无数据状态
// 				cout << "不行" << endl;
// 				DWORD times = GetTickCount() - iter->second;
// 				if (times > 300 * 1000)
// 				{
// 					cout << "客户端：" <<iter->first<< "连接超时" << endl;
// 					closesocket(client);
// 					//iter = _list.erase(iter);
// 				}
// 				else
// 				{
// 					//cout << iter->first << "无数据" << " " << "时间：" << times / 1000.0 << endl;
// 					++iter;
// 				}
// 			}
// 			else 
// 			{       //正常情况下对状态进行更新
// 				cout << "接收正常" << endl;
// 				iter->second = GetTickCount();
// 				buffer[res] = 0;
// 				of.write(buffer, res);
// 				cout << "buffer:" << buffer << endl;
// 				++iter;
// 			}
// 		}
		//qmutex.unlock();
		//Sleep(1000);
 	}
	//of.close();
}
//发送数据
void FileserverSocket::sendThread(SOCKET client)
{
// 	while (true){
// 		UserData send_data(25, "v", "11111", "zhangsaobao", "1900-02-31");
// 		sendMSG(send_data, client);
// 		Sleep(3000);
// 	}	
}

bool FileserverSocket::sendMSG(UserData & send_struct, SOCKET client)
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

ClientList & FileserverSocket::GetClientList()
{
	return clientlist;
}
