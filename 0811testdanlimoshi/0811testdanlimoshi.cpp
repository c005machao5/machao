// 0811testdanlimoshi.cpp : �������̨Ӧ�ó������ڵ㡣
//

// ����ģʽ��
// ��ʵ������ֻ��һ��ʵ��
// (1).ʹ�þ�̬��Ա�������洢ʵ��(ָ��)
// (2)���캯����������(˽��)
// (3)�����ṩ��̬�ӿ�������������ʵ��
// 
// ��̬��Ա������ʼ��(ȫ�ֳ�ʼ��) ��Ϊ���� Ϊ�գ�����ģʽ   ��һ�� �����󣬶���ģʽ
#include "stdafx.h"
#include<iostream>
using namespace std;
class CSingleton
{
public:
	static CSingleton* GetInstance()
	{
		if (m_pInstance == NULL)
			m_pInstance = new CSingleton();
		return m_pInstance;
	}
	void output()
	{
		cout << a << endl;
	}
	~CSingleton()
	{
		delete m_pInstance;
	}
private:
	CSingleton(){ a = 10; };
	int a;
	static CSingleton * m_pInstance;
};
CSingleton * CSingleton::m_pInstance = nullptr;
int _tmain(int argc, _TCHAR* argv[])
{
	CSingleton* p1 = CSingleton::GetInstance();
	p1->output();
	return 0;

}

