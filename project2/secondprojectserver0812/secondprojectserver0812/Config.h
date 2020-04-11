#pragma once
#include <string>
#include<tinyxml.h>
class Config
{
public:
	Config(std::string path);
	std::string  getDatabaseIP(); //数据库IP
	std::string getDatabaseUseName();//数据库用户名
	std::string getDatabasePassword();//数据库密码
	std::string getDatabase(); //数据库名
	std::string getDatabasePort();//数据库端口
	std::string getSocketInfoIP();//socket IP
	std::string getSocketInfoPort();// socket 端口
private:
	TiXmlElement* rootElement;
	TiXmlElement* element;
	TiXmlDocument xml;
};

