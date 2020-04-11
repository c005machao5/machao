// 0811testdanlimoshi.cpp : 定义控制台应用程序的入口点。
//

// 单例模式：
// 类实例化后只有一个实例
// (1).使用静态成员变量来存储实例(指针)
// (2)构造函数隐藏起来(私有)
// (3)对外提供静态接口来产生并返回实例
// 
// 静态成员变量初始化(全局初始化) 分为两种 为空，懒汉模式   另一种 给对象，饿汉模式
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

