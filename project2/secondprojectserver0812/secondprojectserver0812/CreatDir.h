#pragma once
#include <io.h>
#include <direct.h>
#define PATH_DELIMITER '\\'
#include<string>
class CreatDir
{
public:
	CreatDir();
	~CreatDir();
	bool createDirectory( std::string folder);//��·�����ɸ�ʽniuxin\\niuxinword
};

