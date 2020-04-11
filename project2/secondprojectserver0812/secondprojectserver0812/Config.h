#pragma once
#include <string>
#include<tinyxml.h>
class Config
{
public:
	Config(std::string path);
	std::string  getDatabaseIP(); //���ݿ�IP
	std::string getDatabaseUseName();//���ݿ��û���
	std::string getDatabasePassword();//���ݿ�����
	std::string getDatabase(); //���ݿ���
	std::string getDatabasePort();//���ݿ�˿�
	std::string getSocketInfoIP();//socket IP
	std::string getSocketInfoPort();// socket �˿�
private:
	TiXmlElement* rootElement;
	TiXmlElement* element;
	TiXmlDocument xml;
};

