#pragma once
#include "stdafx.h"
#include <mysql.h>

class MysqlDB
{
private:
	static MysqlDB * mysqldb;
	MYSQL *sock;
	MYSQL mysql;
	MYSQL_RES * result;                          //保存结果集的
	void init_sqldb()
	{
		const char * host = "192.168.0.103";  //因为是作为本机测试，所以填写的是本地IP
		const char * user = "root";       //这里改为你的用户名，即连接MySQL的用户名
		const char * passwd = "root"; //这里改为你的用户密码
		const char * db = "1031";      //这里改为你要连接的数据库的名字
		unsigned int port = 3306;           //这是MySQL的服务器的端口，如果你没有修改过的话就是3306。
		const char * unix_socket = NULL;    //unix_socket这是unix下的，我在Windows下，所以就把它设置为NULL
		unsigned long client_flag = 0;      //这个参数一般为0
		const char * i_query = "select * from user_surface"; //查询语句
		mysql_init(&mysql);                          //连接之前必须使用这个函数来初始化
		if ((sock = mysql_real_connect(&mysql, host, user, passwd, db, port, unix_socket, client_flag)) == NULL) //连接MySQL
		{
			printf("连接失败，原因是: \n");
			fprintf(stderr, " %s\n", mysql_error(&mysql));
			exit(1);
		}
		else
		{
			fprintf(stderr, "连接MySQL成功！！\n");
		}
	}
	MysqlDB()
	{
		init_sqldb();
	};
public:
	static MysqlDB * get_instance()
	{
		return mysqldb;
	}
	MYSQL_RES * get_result(const char * query)
	{
		if (mysql_query(&mysql, query) != 0)       //如果连接成功，则开始查询
		{
			fprintf(stderr, "查询失败！\n");
			exit(1);
		}
		if ((result = mysql_store_result(&mysql)) == NULL) //保存查询的结果
		{
			fprintf(stderr, "保存结果集失败！\n");
			exit(1);
		}
		return result;
	}
	bool exce(const char * sql)
	{
		if (mysql_query(&mysql, sql) != 0)       //如果连接成功，则开始查询
		{
			fprintf(stderr, "查询失败！\n");
			return false;
		}
		return true;
	}
	~MysqlDB() {};
private :
	
};
MysqlDB * MysqlDB::mysqldb = new MysqlDB;
