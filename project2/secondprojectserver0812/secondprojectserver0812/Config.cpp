#include "stdafx.h"
#include "Config.h"

#include<iostream>
using namespace std;
Config::Config(std::string path)
{
	xml=path.c_str();////文档对象 传递文件 
	xml.LoadFile();//加载树状
	rootElement = xml.RootElement();
}

std::string Config::getDatabaseIP()
{
	element = rootElement->FirstChildElement("databaseInfo");//获取第一个值为value的子节点，value默认值为空，则返回第一个子节点。
	return std::string(element->Attribute("IP"));
			
}

std::string Config::getDatabaseUseName()
{
	element = rootElement->FirstChildElement("databaseInfo");//获取第一个值为value的子节点，value默认值为空，则返回第一个子节点。

	return std::string(element->Attribute("username"));
}

std::string Config::getDatabasePassword()
{
	element = rootElement->FirstChildElement("databaseInfo");//获取第一个值为value的子节点，value默认值为空，则返回第一个子节点。

	return std::string(element->Attribute("password"));
}

std::string Config::getDatabase()
{
	element = rootElement->FirstChildElement("databaseInfo");//获取第一个值为value的子节点，value默认值为空，则返回第一个子节点。

	return std::string(element->Attribute("database"));
}

std::string Config::getDatabasePort()
{
	element = rootElement->FirstChildElement("databaseInfo");//获取第一个值为value的子节点，value默认值为空，则返回第一个子节点。
	return std::string(element->Attribute("port"));
}

std::string Config::getSocketInfoIP()
{
	element = rootElement->FirstChildElement("socketInfo");//获取第一个值为value的子节点，value默认值为空，则返回第一个子节点。
	return std::string(element->Attribute("IP"));
}

std::string Config::getSocketInfoPort()
{
	element = rootElement->FirstChildElement("socketInfo");//获取第一个值为value的子节点，value默认值为空，则返回第一个子节点。
	return std::string(element->Attribute("port"));

}

