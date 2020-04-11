#include "stdafx.h"
#include "Config.h"

#include<iostream>
using namespace std;
Config::Config(std::string path)
{
	xml=path.c_str();////�ĵ����� �����ļ� 
	xml.LoadFile();//������״
	rootElement = xml.RootElement();
}

std::string Config::getDatabaseIP()
{
	element = rootElement->FirstChildElement("databaseInfo");//��ȡ��һ��ֵΪvalue���ӽڵ㣬valueĬ��ֵΪ�գ��򷵻ص�һ���ӽڵ㡣
	return std::string(element->Attribute("IP"));
			
}

std::string Config::getDatabaseUseName()
{
	element = rootElement->FirstChildElement("databaseInfo");//��ȡ��һ��ֵΪvalue���ӽڵ㣬valueĬ��ֵΪ�գ��򷵻ص�һ���ӽڵ㡣

	return std::string(element->Attribute("username"));
}

std::string Config::getDatabasePassword()
{
	element = rootElement->FirstChildElement("databaseInfo");//��ȡ��һ��ֵΪvalue���ӽڵ㣬valueĬ��ֵΪ�գ��򷵻ص�һ���ӽڵ㡣

	return std::string(element->Attribute("password"));
}

std::string Config::getDatabase()
{
	element = rootElement->FirstChildElement("databaseInfo");//��ȡ��һ��ֵΪvalue���ӽڵ㣬valueĬ��ֵΪ�գ��򷵻ص�һ���ӽڵ㡣

	return std::string(element->Attribute("database"));
}

std::string Config::getDatabasePort()
{
	element = rootElement->FirstChildElement("databaseInfo");//��ȡ��һ��ֵΪvalue���ӽڵ㣬valueĬ��ֵΪ�գ��򷵻ص�һ���ӽڵ㡣
	return std::string(element->Attribute("port"));
}

std::string Config::getSocketInfoIP()
{
	element = rootElement->FirstChildElement("socketInfo");//��ȡ��һ��ֵΪvalue���ӽڵ㣬valueĬ��ֵΪ�գ��򷵻ص�һ���ӽڵ㡣
	return std::string(element->Attribute("IP"));
}

std::string Config::getSocketInfoPort()
{
	element = rootElement->FirstChildElement("socketInfo");//��ȡ��һ��ֵΪvalue���ӽڵ㣬valueĬ��ֵΪ�գ��򷵻ص�һ���ӽڵ㡣
	return std::string(element->Attribute("port"));

}

