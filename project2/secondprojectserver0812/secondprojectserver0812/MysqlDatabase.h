#pragma once
#include "Config.h"
#include<WinSock2.h>
#include<string>
#include<mysql.h>
#include<iostream>
class MysqlDatabase
{
public:
	static MysqlDatabase * get_instance();
	bool Open();  // 打开连接
	void Close(); // 关闭连接
	MYSQL_RES* queryData(std::string sql);
	MYSQL_RES* insertData(std::string sql);
	MYSQL_RES* deleteData(std::string sql);
	MYSQL_RES* changeData(std::string sql);
private:	
	MysqlDatabase();
	static MysqlDatabase* mysql_database;
	MYSQL m_mysql;
	MYSQL_RES *m_res;

};

