// secondprojectserver0812.cpp : 定义控制台应用程序的入口点。

#include "stdafx.h"
#include "CreatDir.h"
#include<WinSock2.h>
#include "MysqlDatabase.h"
#include "ServerSocket.h"
#include<iostream>
#include<string>
#include "LogClass.h"
#pragma comment(lib, "ws2_32.lib") 

using namespace std;
int main()
{

// 	ServerSocket ser;
// 	ser.createSocket();
	int a = 0;
 	int b = 1;
// 	const int*p = &a;
// 	p = &b;
	//cout << *p << endl;
 	int const*p = &a;
 	p = &b;
 	cout << *p << endl;
}

// 	MysqlDatabase* mysqlDatabase = MysqlDatabase::get_instance();
// 	mysqlDatabase->Open();
// 	MYSQL_RES *res;
// 	MYSQL_ROW row;
// 	res=mysqlDatabase->queryData("select * from  t1_user ");
// 	while ((row = mysql_fetch_row(res)) != NULL)
// 	{
// 		for (size_t i = 0; i < mysql_num_fields(res); ++i)
// 		{
// 			cout << row[i] << "/t";
// 		}
// 		cout << endl;
// 	}
// 	mysql_free_result(res);
// LogClass log("daily_logger", "D:/logs/daily.txt");
// log.write_Info("q的值为9", __LINE__, __FILE__, __FUNCTION__);
// log.write_error("q的值为10", __LINE__, __FILE__, __FUNCTION__);

// 	BOOL ret;
// 	LPCWSTR dirPath1 = _T("D:\\user\\niuxin0816");
// 	ret = CreateDirectory(dirPath1, 0);
// 	if (ret == 0) 
// 	{
// 		printf("CreateDirectory fail(%d)\n", GetLastError());
// 	}
// 	else
// 	{
// 		printf("CreateDirectory -> %d\n", ret);
// 	}
// 	system("pause");//system("PAUSE")  是暂停的意思，等待用户信号；不然控制台程序会一闪即过，你来不及看到执行结果。
// 	
// CreatDir creatdir;
// string path = "D:\\user\\niuxin";
// creatdir.createDirectory(path);