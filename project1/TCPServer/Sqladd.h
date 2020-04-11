#pragma once
#include <string>
#include<ctime>
#include<iostream>
#include"StructData.h"
using namespace std;

class Sqladd
{
public:
	Sqladd();
	~Sqladd();
	const string inquire_name(const struct UserData name);//注册查询
	const string RegSql(const struct UserData senduserdata);//登录查询
	const string Logstr(const struct LoginInfo loguserdata);//查权限
	string insert(struct UserData userinfo);//插入用户信息注册
	string createSql(struct Data_Selection m_data_selection);//历史查询
	string createSql(struct Data_Analysis m_data_analysis);//数据分析
};

