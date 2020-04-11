#pragma once
#include "stdafx.h"
#include <mysql.h>

class MysqlDB
{
private:
	static MysqlDB * mysqldb;
	MYSQL *sock;
	MYSQL mysql;
	MYSQL_RES * result;                          //����������
	void init_sqldb()
	{
		const char * host = "192.168.0.103";  //��Ϊ����Ϊ�������ԣ�������д���Ǳ���IP
		const char * user = "root";       //�����Ϊ����û�����������MySQL���û���
		const char * passwd = "root"; //�����Ϊ����û�����
		const char * db = "1031";      //�����Ϊ��Ҫ���ӵ����ݿ������
		unsigned int port = 3306;           //����MySQL�ķ������Ķ˿ڣ������û���޸Ĺ��Ļ�����3306��
		const char * unix_socket = NULL;    //unix_socket����unix�µģ�����Windows�£����ԾͰ�������ΪNULL
		unsigned long client_flag = 0;      //�������һ��Ϊ0
		const char * i_query = "select * from user_surface"; //��ѯ���
		mysql_init(&mysql);                          //����֮ǰ����ʹ�������������ʼ��
		if ((sock = mysql_real_connect(&mysql, host, user, passwd, db, port, unix_socket, client_flag)) == NULL) //����MySQL
		{
			printf("����ʧ�ܣ�ԭ����: \n");
			fprintf(stderr, " %s\n", mysql_error(&mysql));
			exit(1);
		}
		else
		{
			fprintf(stderr, "����MySQL�ɹ�����\n");
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
		if (mysql_query(&mysql, query) != 0)       //������ӳɹ�����ʼ��ѯ
		{
			fprintf(stderr, "��ѯʧ�ܣ�\n");
			exit(1);
		}
		if ((result = mysql_store_result(&mysql)) == NULL) //�����ѯ�Ľ��
		{
			fprintf(stderr, "��������ʧ�ܣ�\n");
			exit(1);
		}
		return result;
	}
	bool exce(const char * sql)
	{
		if (mysql_query(&mysql, sql) != 0)       //������ӳɹ�����ʼ��ѯ
		{
			fprintf(stderr, "��ѯʧ�ܣ�\n");
			return false;
		}
		return true;
	}
	~MysqlDB() {};
private :
	
};
MysqlDB * MysqlDB::mysqldb = new MysqlDB;
