#include "stdafx.h"
#include "MysqlDatabase.h"
using namespace std;

MysqlDatabase* MysqlDatabase::get_instance()
{
	if (mysql_database == NULL)
		mysql_database = new MysqlDatabase();
	return mysql_database;
}
MysqlDatabase::MysqlDatabase()
{
	mysql_init(&m_mysql);
	mysql_options(&m_mysql, MYSQL_SET_CHARSET_NAME, "GBK");
}

bool MysqlDatabase::Open()
{
	Config config("D:\\configure.xml");
	if (mysql_real_connect(&m_mysql, config.getDatabaseIP().c_str(), config.getDatabaseUseName().c_str()\
		, config.getDatabasePassword().c_str()\
		, config.getDatabase().c_str(), atoi(config.getDatabasePort().c_str()), NULL, 0))
	{
		cout << "数据库连接成功" << endl;
		return true;
	}
	else
	{
		return false;
	}
}

void MysqlDatabase::Close()
{
	mysql_free_result(m_res);
	mysql_close(&m_mysql);
}

MYSQL_RES * MysqlDatabase::queryData(std::string sql)
{
	if (mysql_real_query(&m_mysql, sql.c_str(), sql.size())!=0)
	{
		std::cout << "查询失败" <<	endl;
		//exit(1);
	}
	if ((m_res = mysql_store_result(&m_mysql)) == NULL) //保存查询的结果
	{
		std::cout << "保存结果失败" << endl;
		exit(1);
	}
	return m_res;
}

MYSQL_RES * MysqlDatabase::insertData(std::string sql)
{
	if (mysql_real_query(&m_mysql, sql.c_str(), sql.size()) != 0)
	{
		std::cout << "查询失败" << endl;
		exit(1);
	}
	if ((m_res = mysql_store_result(&m_mysql)) == NULL) //保存查询的结果
	{
		std::cout << "保存结果失败" << endl;
		exit(1);
	}
	return m_res;
}

MYSQL_RES * MysqlDatabase::deleteData(std::string sql)
{
	if (mysql_real_query(&m_mysql, sql.c_str(), sql.size()) != 0)
	{
		std::cout << "查询失败" << endl;
		exit(1);
	}
	if ((m_res = mysql_store_result(&m_mysql)) == NULL) //保存查询的结果
	{
		std::cout << "保存结果失败" << endl;
		exit(1);
	}
	return m_res;
}


MYSQL_RES * MysqlDatabase::changeData(std::string sql)
{
	if (mysql_real_query(&m_mysql, sql.c_str(), sql.size()) != 0)
	{
		std::cout << "查询失败" << endl;
		exit(1);
	}
	if ((m_res = mysql_store_result(&m_mysql)) == NULL) //保存查询的结果
	{
		std::cout << "保存结果失败" << endl;
		exit(1);
	}
	return m_res;
}

MysqlDatabase* MysqlDatabase::mysql_database =nullptr;