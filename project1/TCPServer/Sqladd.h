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
	const string inquire_name(const struct UserData name);//ע���ѯ
	const string RegSql(const struct UserData senduserdata);//��¼��ѯ
	const string Logstr(const struct LoginInfo loguserdata);//��Ȩ��
	string insert(struct UserData userinfo);//�����û���Ϣע��
	string createSql(struct Data_Selection m_data_selection);//��ʷ��ѯ
	string createSql(struct Data_Analysis m_data_analysis);//���ݷ���
};

